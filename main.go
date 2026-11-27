package main

import (
 "bytes"
 "crypto/sha256"
 "io/fs"
 "context"
 "encoding/json"
 "errors"
 "fmt"
 "html/template"
 "log"
 "net/http"
 "os"
 "os/exec"
 "path/filepath"
 "regexp"
 "sort"
 "strings"
 "sync"
 "syscall"
 "time"
)
type Sample struct { Input string `json:"input"`; Output string `json:"output"` }
type Problem struct { Difficulty string `json:"difficulty"`; GeneratorArgs [][]string `json:"generatorArgs,omitempty"`; Title string `json:"title"`; Statement string `json:"statement"`; Editorial string `json:"editorial"`; Samples []Sample `json:"samples"`; Hidden []string `json:"hidden,omitempty"` }
type Entry struct { Problem; Dir,Section,Slug,Suite string; Solved bool }
type Page struct { Groups map[string][]*Entry; Sections []string; Task *Entry; Verdict,Code string; Builder,Editorial bool; Form Problem; Section,Slug,Solution,Generator,Commands,Revision string }
var catalog=map[string]*Entry{}
var gate sync.Mutex
var valid=regexp.MustCompile("^[A-Za-z0-9_-]+$")
var view=template.Must(template.ParseFiles("page.html"))

type capped struct { buf bytes.Buffer; remaining int }
func (w *capped) Write(p []byte)(int,error){
 if len(p)>w.remaining{return 0,errors.New("output limit exceeded")}
 w.remaining-=len(p);return w.buf.Write(p)
}
func run(dir string,input string,limit time.Duration,name string,args ...string)(string,error){
 ctx,cancel:=context.WithTimeout(context.Background(),limit);defer cancel()
 cmd:=exec.CommandContext(ctx,name,args...);cmd.Dir=dir;cmd.Stdin=strings.NewReader(input)
 cmd.SysProcAttr=&syscall.SysProcAttr{Setpgid:true}
 cmd.Cancel=func() error{return syscall.Kill(-cmd.Process.Pid,syscall.SIGKILL)}
 cmd.WaitDelay=time.Second
 out,diag:=&capped{remaining:8<<20},&capped{remaining:64<<10};cmd.Stdout=out;cmd.Stderr=diag
 err:=cmd.Run();if cmd.Process!=nil{syscall.Kill(-cmd.Process.Pid,syscall.SIGKILL)}
 if ctx.Err()!=nil{return "",ctx.Err()};if err!=nil{return "",fmt.Errorf("%w %s",err,diag.buf.String())};return out.buf.String(),nil
}
func compile(dir,src,bin string)error{lib,err:=filepath.Abs("lib");if err!=nil{return err};_,err=run(dir,"",30*time.Second,"g++","-std=c++20","-O2","-I",lib,src,"-o",bin);return err}
func same(a,b string)bool{return strings.Join(strings.Fields(a)," ")==strings.Join(strings.Fields(b)," ")}
// Linux LP64 C++ integer limits. Keep the author's symbolic spelling on disk.
func generatorArguments(args []string) []string {
 limits := map[string]string{
  "INT_MIN": "-2147483648", "INT_MAX": "2147483647",
  "LONG_MIN": "-9223372036854775808", "LONG_MAX": "9223372036854775807",
 }
 expanded := append([]string(nil), args...)
 for i, arg := range expanded {
  if value, ok := limits[arg]; ok { expanded[i] = value }
 }
 return expanded
}
func build(e *Entry)(string,error){
 tests:=filepath.Join(e.Dir,"tests");suite,err:=os.MkdirTemp(tests,"suite-");if err!=nil{return "",err}
 ok:=false;defer func(){if !ok{os.RemoveAll(suite)}}()
 for _,d:=range []string{"in","out"}{if err=os.Mkdir(filepath.Join(suite,d),0755);err!=nil{return "",err}}
 if err=compile(suite,tests+"/sol.cpp","sol");err!=nil{return "",err}
 inputs:=[]string{};for _,s:=range e.Samples{inputs=append(inputs,s.Input)};inputs=append(inputs,e.Hidden...)
 if _,err=os.Stat(tests+"/gen.cpp");err==nil{if err=compile(suite,tests+"/gen.cpp","gen");err!=nil{return "",err};runs:=e.GeneratorArgs;if len(runs)==0{runs=[][]string{nil}};for _,args:=range runs{input,err:=run(suite,"",5*time.Second,"./gen",generatorArguments(args)...);if err!=nil{return "",fmt.Errorf("generator %v: %w",args,err)};inputs=append(inputs,input)}}
 if len(inputs)==0{return "",errors.New("add at least one case")}
 for i,s:=range inputs{o,err:=run(suite,s,3*time.Second,"./sol");if err!=nil{return "",err};if i<len(e.Samples)&&!same(o,e.Samples[i].Output){return "",fmt.Errorf("sample %d: expected %q, reference produced %q",i+1,e.Samples[i].Output,o)}
 for dir,data:=range map[string]string{"in":s,"out":o}{if err=os.WriteFile(filepath.Join(suite,dir,fmt.Sprintf("%06d",i+1)),[]byte(data),0644);err!=nil{return "",err}}}
 os.Remove(suite+"/sol");os.Remove(suite+"/gen");ok=true;return suite,nil
}
func load(dir string,force bool)error{
 b,err:=os.ReadFile(dir+"/meta.json");if err!=nil{return err};e:=&Entry{Dir:dir,Section:filepath.Base(filepath.Dir(dir)),Slug:filepath.Base(dir)};if err=json.Unmarshal(b,&e.Problem);err!=nil{return err}
 if err=e.validateDifficulty();err!=nil{return err}
 // Only reuse the suite named by the last successful build.
 marker:=dir+"/tests/current";old,_:=os.ReadFile(marker);e.Suite=filepath.Join(dir,"tests",string(old))
 cached,cacheErr:=os.ReadDir(e.Suite+"/in")
 stale:=len(e.GeneratorArgs)>0 && len(cached)!=len(e.Samples)+len(e.Hidden)+len(e.GeneratorArgs)
 if force||len(old)==0||cacheErr!=nil||stale{suite,err:=build(e);if err!=nil{return err};if err=os.WriteFile(marker+".tmp",[]byte(filepath.Base(suite)),0644);err!=nil{return err};if err=os.Rename(marker+".tmp",marker);err!=nil{return err};if strings.HasPrefix(string(old),"suite-")&&filepath.Base(string(old))==string(old){os.RemoveAll(e.Suite)};e.Suite=suite}
 catalog[e.Section+"/"+e.Slug]=e;return nil
}
func judge(e *Entry,code string)(string,error){
 tmp,err:=os.MkdirTemp("","practice-");if err!=nil{return "",err};defer os.RemoveAll(tmp)
 if err=os.WriteFile(tmp+"/main.cpp",[]byte(code),0600);err!=nil{return "",err}
 if err=compile(tmp,"main.cpp","main");err!=nil{return "Compilation failed\n"+err.Error(),nil}
 files,err:=os.ReadDir(e.Suite+"/in");if err!=nil||len(files)==0{return "",errors.New("test suite unavailable")}
 var slow time.Duration
 for i,f:=range files{in,err:=os.ReadFile(e.Suite+"/in/"+f.Name());if err!=nil{return "",err};want,err:=os.ReadFile(e.Suite+"/out/"+f.Name());if err!=nil{return "",err}
 start:=time.Now();got,err:=run(tmp,string(in),2*time.Second,"./main");elapsed:=time.Since(start);slow=max(slow,elapsed);v:=""
 switch {case errors.Is(err,context.DeadlineExceeded):v="Time limit exceeded";case err!=nil:v="Runtime or output error";case !same(got,string(want)):v="Wrong answer"}
 if v!=""{return fmt.Sprintf("%s · Case %d of %d · %d ms",v,i+1,len(files),elapsed.Milliseconds()),nil}}
 e.Solved=true;return fmt.Sprintf("Accepted · %d cases · Slowest %d ms",len(files),slow.Milliseconds()),nil
}
var difficultyRank = map[string]int{"easy": 0, "medium": 1, "hard": 2}

func (p *Problem) validateDifficulty() error {
 if p.Difficulty == "" { p.Difficulty = "easy" }
 if _, ok := difficultyRank[p.Difficulty]; !ok {
  return fmt.Errorf("unknown difficulty %q: choose easy, medium or hard", p.Difficulty)
 }
 return nil
}

func readBuilder(p *Page,e *Entry) error {
 meta,err:=os.ReadFile(e.Dir+"/meta.json")
 if err!=nil{return err}
 if err=json.Unmarshal(meta,&p.Form);err!=nil{return err}
 if err=p.Form.validateDifficulty();err!=nil{return err}
 p.Section=e.Section
 p.Slug=e.Slug
 sol,err:=os.ReadFile(e.Dir+"/tests/sol.cpp")
 if err!=nil{return err}
 gen,err:=os.ReadFile(e.Dir+"/tests/gen.cpp")
 if err!=nil&&!os.IsNotExist(err){return err}
 p.Solution=string(sol)
 p.Generator=string(gen)
 for _,args:=range p.Form.GeneratorArgs{p.Commands+=strings.TrimSpace("gen "+strings.Join(args," "))+"\n"}
 p.Revision=fmt.Sprintf("%x",sha256.Sum256([]byte(fmt.Sprintf("%q:%q:%q",meta,sol,gen))))
 return nil
}
func saveProblem(r *http.Request,page *Page,existing *Entry)(string,error){
 section:=strings.ReplaceAll(strings.TrimSpace(r.FormValue("section"))," ","_");slug:=r.FormValue("slug")
 p:=Problem{Difficulty:r.FormValue("difficulty"),Title:r.FormValue("title"),Statement:r.FormValue("statement"),Editorial:r.FormValue("editorial")}
 inputs,outputs:=r.PostForm["input"],r.PostForm["output"]
 if len(inputs)!=len(outputs){return "",errors.New("each sample needs an input and output field")}
 for i,input:=range inputs{p.Samples=append(p.Samples,Sample{input,outputs[i]})}
 for _,input:=range r.PostForm["hidden"]{if input!=""{p.Hidden=append(p.Hidden,input)}}
 page.Form=p;page.Section=section;page.Slug=slug;page.Commands=r.FormValue("commands");page.Solution=r.FormValue("solution");page.Generator=r.FormValue("generator");page.Revision=r.FormValue("revision")
 if err:=p.validateDifficulty();err!=nil{return "",err}
 for line,command:=range strings.Split(page.Commands,"\n"){
  fields:=strings.Fields(command)
  if len(fields)==0{continue}
  if fields[0]!="gen"&&fields[0]!="./gen"{return "",fmt.Errorf("command line %d must start with gen",line+1)}
  if strings.TrimSpace(page.Generator)==""{return "",errors.New("add generator source for the listed commands")}
  p.GeneratorArgs=append(p.GeneratorArgs,fields[1:])
 }
 if !valid.MatchString(section)||!valid.MatchString(slug){return "",errors.New("invalid section or slug")}
 if existing!=nil{
  var disk Page
  if err:=readBuilder(&disk,existing);err!=nil{return "",err}
  if disk.Revision!=page.Revision{return "",errors.New("problem changed since opening; reload before saving")}
 }
 parent,_:=filepath.Abs(filepath.Join("problems",section));if err:=os.MkdirAll(parent,0755);err!=nil{return "",err}
 dest:=filepath.Join(parent,slug)
 if existing==nil||dest!=existing.Dir{if _,err:=os.Stat(dest);!os.IsNotExist(err){return "",errors.New("destination already exists")}}
 dir,err:=os.MkdirTemp(parent,".draft-");if err!=nil{return "",err};defer os.RemoveAll(dir)
 if existing!=nil{
  err=filepath.WalkDir(existing.Dir,func(path string,item fs.DirEntry,err error)error{
   if err!=nil{return err};rel,err:=filepath.Rel(existing.Dir,path);if err!=nil{return err}
   if rel=="."{return nil}
   if filepath.Dir(rel)=="tests"&&item.IsDir()&&strings.HasPrefix(item.Name(),"suite-"){return filepath.SkipDir}
   if rel=="tests/current"||rel=="tests/gen.cpp"{return nil}
   target:=filepath.Join(dir,rel)
   if item.IsDir(){return os.MkdirAll(target,0755)}
   if item.Type()&os.ModeSymlink!=0{link,err:=os.Readlink(path);if err!=nil{return err};return os.Symlink(link,target)}
   data,err:=os.ReadFile(path);if err!=nil{return err};info,err:=item.Info();if err!=nil{return err};return os.WriteFile(target,data,info.Mode().Perm())
  });if err!=nil{return "",err}
 }
 if err=os.MkdirAll(dir+"/tests",0755);err!=nil{return "",err};b,_:=json.MarshalIndent(p,"","  ")
 files:=map[string]string{"meta.json":string(b),"tests/sol.cpp":r.FormValue("solution")};if g:=r.FormValue("generator");g!=""{files["tests/gen.cpp"]=g}
 for path,data:=range files{if err=os.WriteFile(dir+"/"+path,[]byte(data),0644);err!=nil{return "",err}}
 suite,err:=build(&Entry{Problem:p,Dir:dir});if err!=nil{return "",err};if err=os.WriteFile(dir+"/tests/current",[]byte(filepath.Base(suite)),0644);err!=nil{return "",err}
 backup:=""
 if existing!=nil{
  backup,err=os.MkdirTemp(filepath.Dir(existing.Dir),".previous-");if err!=nil{return "",err}
  if err=os.Rename(existing.Dir,backup+"/problem");err!=nil{os.Remove(backup);return "",err}
 }
 if err=os.Rename(dir,dest);err!=nil{
  if backup!=""{if restore:=os.Rename(backup+"/problem",existing.Dir);restore!=nil{return "",fmt.Errorf("restore previous problem from %s: %w",backup,restore)};os.Remove(backup)}
  return "",err
 }
 if existing!=nil{delete(catalog,existing.Section+"/"+existing.Slug);os.RemoveAll(backup)}
 key:=section+"/"+slug
 catalog[key]=&Entry{Problem:p,Section:section,Slug:slug,Dir:dest,Suite:filepath.Join(dest,"tests",filepath.Base(suite))}
 return key,nil
}
func serve(w http.ResponseWriter,r *http.Request){
 if r.Host!="127.0.0.1:8000"&&r.Host!="localhost:8000"{http.Error(w,"invalid host",403);return}
 if r.Method=="GET" && (r.URL.Path=="/assets/app.js" || r.URL.Path=="/assets/prism.js" || r.URL.Path=="/assets/style.css"){http.ServeFile(w,r,"web/"+filepath.Base(r.URL.Path));return}
 gate.Lock();defer gate.Unlock()
 p:=Page{Groups:map[string][]*Entry{},Builder:r.URL.Path=="/builder"};key:=r.URL.Query().Get("id");p.Task=catalog[key];p.Editorial=r.URL.Path=="/editorial"
 if key!=""&&p.Task==nil{http.NotFound(w,r);return}
 if p.Builder&&r.Method=="GET"&&p.Task!=nil{if err:=readBuilder(&p,p.Task);err!=nil{http.Error(w,err.Error(),500);return}}
 if r.Method=="POST"{if r.Header.Get("Origin")!="http://"+r.Host{http.Error(w,"invalid origin",403);return};r.Body=http.MaxBytesReader(w,r.Body,1<<20);if err:=r.ParseForm();err!=nil{http.Error(w,"invalid form",400);return}
 var err error
 switch {case p.Builder:key,err=saveProblem(r,&p,p.Task);if err==nil{http.Redirect(w,r,"/task?id="+key,303);return}
 case r.URL.Path=="/task"&&p.Task!=nil:p.Code=r.FormValue("code");p.Verdict,err=judge(p.Task,p.Code)
 default:http.NotFound(w,r);return};if err!=nil{p.Verdict=err.Error()}}
 if (r.URL.Path=="/task"||p.Editorial)&&p.Task==nil||r.URL.Path!="/"&&r.URL.Path!="/task"&&!p.Builder&&!p.Editorial{http.NotFound(w,r);return}
 sections,_:=os.ReadDir("problems");for _,s:=range sections{if s.IsDir(){p.Sections=append(p.Sections,strings.ReplaceAll(s.Name(),"_"," "))}}
 keys:=[]string{};for k:=range catalog{keys=append(keys,k)};sort.Strings(keys);for _,k:=range keys{e:=catalog[k];s:=strings.ReplaceAll(e.Section,"_"," ");p.Groups[s]=append(p.Groups[s],e)}
 for _, tasks := range p.Groups {
  sort.SliceStable(tasks, func(i,j int) bool {
   return difficultyRank[tasks[i].Difficulty] < difficultyRank[tasks[j].Difficulty]
  })
 }
 w.Header().Set("Content-Type","text/html; charset=utf-8");if err:=view.Execute(w,p);err!=nil{log.Print(err)}
}
func main(){root,_:=filepath.Abs("problems");paths,_:=filepath.Glob(root+"/*/*/meta.json");force:=len(os.Args)>1&&os.Args[1]=="build";failed:=false;for _,path:=range paths{if err:=load(filepath.Dir(path),force);err!=nil{log.Print(path,": ",err);failed=true}};if force{if failed{os.Exit(1)};return};log.Print("http://127.0.0.1:8000");log.Fatal(http.ListenAndServe("127.0.0.1:8000",http.HandlerFunc(serve)))}
