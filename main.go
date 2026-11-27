package main

import (
 "bytes"
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
type Problem struct { Title string `json:"title"`; Statement string `json:"statement"`; Editorial string `json:"editorial"`; Samples []Sample `json:"samples"`; Hidden []string `json:"hidden,omitempty"` }
type Entry struct { Problem; Dir,Section,Slug,Suite string; Solved bool }
type Page struct { Groups map[string][]*Entry; Sections []string; Task *Entry; Verdict,Code string; Builder bool }
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
func compile(dir,src,bin string)error{_,err:=run(dir,"",30*time.Second,"g++","-std=c++20","-O2",src,"-o",bin);return err}
func same(a,b string)bool{return strings.Join(strings.Fields(a)," ")==strings.Join(strings.Fields(b)," ")}
func build(e *Entry)(string,error){
 tests:=filepath.Join(e.Dir,"tests");suite,err:=os.MkdirTemp(tests,"suite-");if err!=nil{return "",err}
 ok:=false;defer func(){if !ok{os.RemoveAll(suite)}}()
 for _,d:=range []string{"in","out"}{if err=os.Mkdir(filepath.Join(suite,d),0755);err!=nil{return "",err}}
 if err=compile(suite,tests+"/sol.cpp","sol");err!=nil{return "",err}
 inputs:=[]string{};for _,s:=range e.Samples{inputs=append(inputs,s.Input)};inputs=append(inputs,e.Hidden...)
 if _,err=os.Stat(tests+"/gen.cpp");err==nil{if err=compile(suite,tests+"/gen.cpp","gen");err!=nil{return "",err};s,err:=run(suite,"",5*time.Second,"./gen");if err!=nil{return "",err};inputs=append(inputs,s)}
 if len(inputs)==0{return "",errors.New("add at least one case")}
 for i,s:=range inputs{o,err:=run(suite,s,3*time.Second,"./sol");if err!=nil{return "",err};if i<len(e.Samples)&&!same(o,e.Samples[i].Output){return "",fmt.Errorf("sample %d: expected %q, reference produced %q",i+1,e.Samples[i].Output,o)}
 for dir,data:=range map[string]string{"in":s,"out":o}{if err=os.WriteFile(filepath.Join(suite,dir,fmt.Sprintf("%06d",i+1)),[]byte(data),0644);err!=nil{return "",err}}}
 os.Remove(suite+"/sol");os.Remove(suite+"/gen");ok=true;return suite,nil
}
func load(dir string,force bool)error{
 b,err:=os.ReadFile(dir+"/meta.json");if err!=nil{return err};e:=&Entry{Dir:dir,Section:filepath.Base(filepath.Dir(dir)),Slug:filepath.Base(dir)};if err=json.Unmarshal(b,&e.Problem);err!=nil{return err}
 // Only reuse the suite named by the last successful build.
 marker:=dir+"/tests/current";old,_:=os.ReadFile(marker);e.Suite=filepath.Join(dir,"tests",string(old))
 if _,err=os.Stat(e.Suite+"/in");force||len(old)==0||err!=nil{suite,err:=build(e);if err!=nil{return err};if err=os.WriteFile(marker+".tmp",[]byte(filepath.Base(suite)),0644);err!=nil{return err};if err=os.Rename(marker+".tmp",marker);err!=nil{return err};if strings.HasPrefix(string(old),"suite-")&&filepath.Base(string(old))==string(old){os.RemoveAll(e.Suite)};e.Suite=suite}
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
func create(r *http.Request)(string,error){
 section:=strings.ReplaceAll(strings.TrimSpace(r.FormValue("section"))," ","_");slug:=r.FormValue("slug")
 if !valid.MatchString(section)||!valid.MatchString(slug){return "",errors.New("invalid section or slug")}
 parent,_:=filepath.Abs(filepath.Join("problems",section));if err:=os.MkdirAll(parent,0755);err!=nil{return "",err}
 dir,err:=os.MkdirTemp(parent,".draft-");if err!=nil{return "",err};defer os.RemoveAll(dir)
 p:=Problem{Title:r.FormValue("title"),Statement:r.FormValue("statement"),Editorial:r.FormValue("editorial"),Samples:[]Sample{{r.FormValue("input"),r.FormValue("output")}}}
 if s:=r.FormValue("hidden");s!=""{p.Hidden=[]string{s}}
 if err=os.Mkdir(dir+"/tests",0755);err!=nil{return "",err};b,_:=json.MarshalIndent(p,"","  ")
 files:=map[string]string{"meta.json":string(b),"tests/sol.cpp":r.FormValue("solution")};if g:=r.FormValue("generator");g!=""{files["tests/gen.cpp"]=g}
 for path,data:=range files{if err=os.WriteFile(dir+"/"+path,[]byte(data),0644);err!=nil{return "",err}}
 suite,err:=build(&Entry{Problem:p,Dir:dir});if err!=nil{return "",err};if err=os.WriteFile(dir+"/tests/current",[]byte(filepath.Base(suite)),0644);err!=nil{return "",err}
 dest:=filepath.Join(parent,slug);if _,err=os.Stat(dest);!os.IsNotExist(err){return "",errors.New("destination already exists")};if err=os.Rename(dir,dest);err!=nil{return "",err};return section+"/"+slug,load(dest,false)
}
func serve(w http.ResponseWriter,r *http.Request){
 if r.Host!="127.0.0.1:8000"&&r.Host!="localhost:8000"{http.Error(w,"invalid host",403);return}
 gate.Lock();defer gate.Unlock()
 p:=Page{Groups:map[string][]*Entry{},Builder:r.URL.Path=="/builder"};key:=r.URL.Query().Get("id");p.Task=catalog[key]
 if r.Method=="POST"{if r.Header.Get("Origin")!="http://"+r.Host{http.Error(w,"invalid origin",403);return};r.Body=http.MaxBytesReader(w,r.Body,1<<20);if err:=r.ParseForm();err!=nil{http.Error(w,"invalid form",400);return}
 var err error
 switch {case p.Builder:key,err=create(r);if err==nil{http.Redirect(w,r,"/task?id="+key,303);return}
 case r.URL.Path=="/task"&&p.Task!=nil:p.Code=r.FormValue("code");p.Verdict,err=judge(p.Task,p.Code)
 default:http.NotFound(w,r);return};if err!=nil{p.Verdict=err.Error()}}
 if r.URL.Path=="/task"&&p.Task==nil||r.URL.Path!="/"&&r.URL.Path!="/task"&&!p.Builder{http.NotFound(w,r);return}
 sections,_:=os.ReadDir("problems");for _,s:=range sections{if s.IsDir(){p.Sections=append(p.Sections,strings.ReplaceAll(s.Name(),"_"," "))}}
 keys:=[]string{};for k:=range catalog{keys=append(keys,k)};sort.Strings(keys);for _,k:=range keys{e:=catalog[k];s:=strings.ReplaceAll(e.Section,"_"," ");p.Groups[s]=append(p.Groups[s],e)}
 w.Header().Set("Content-Type","text/html; charset=utf-8");if err:=view.Execute(w,p);err!=nil{log.Print(err)}
}
func main(){root,_:=filepath.Abs("problems");paths,_:=filepath.Glob(root+"/*/*/meta.json");force:=len(os.Args)>1&&os.Args[1]=="build";failed:=false;for _,path:=range paths{if err:=load(filepath.Dir(path),force);err!=nil{log.Print(path,": ",err);failed=true}};if force{if failed{os.Exit(1)};return};log.Print("http://127.0.0.1:8000");log.Fatal(http.ListenAndServe("127.0.0.1:8000",http.HandlerFunc(serve)))}
