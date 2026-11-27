package main

import (
    "net/http/httptest"
    "net/url"
    "os"
    "path/filepath"
    "strings"
    "testing"
)

func TestBundledTask(t *testing.T) {
    dir, err := filepath.Abs("problems/Binary_Search/last-occurrence")
    if err != nil { t.Fatal(err) }
    if err := load(dir,true); err != nil { t.Fatal(err) }
    e := catalog["Binary_Search/last-occurrence"]
    reference, err := os.ReadFile(dir+"/tests/sol.cpp")
    if err != nil { t.Fatal(err) }
    for _, test := range []struct{code, verdict string}{
        {"int main(){}", "Wrong answer · Case 1"},
        {string(reference), "Accepted"},
    } {
        verdict, err := judge(e,test.code)
        if err != nil || !strings.HasPrefix(verdict,test.verdict) { t.Fatalf("%s: %v",verdict,err) }
    }
    for _, path := range []string{"/","/builder","/task?id="+url.QueryEscape("Binary_Search/last-occurrence")} {
        w := httptest.NewRecorder()
        serve(w,httptest.NewRequest("GET","http://localhost:8000"+path,nil))
        if w.Code != 200 || !strings.Contains(w.Body.String(),"</html>") { t.Fatalf("render %s: %d",path,w.Code) }
    }
}

func TestBuilderCommandsAndEdit(t *testing.T) {
    sectionDir,err:=os.MkdirTemp("problems","builder-test-")
    if err!=nil{t.Fatal(err)}
    defer os.RemoveAll(sectionDir)
    section:=filepath.Base(sectionDir)
    key:=section+"/sum"
    defer delete(catalog,key)
    form:=url.Values{
        "section":{section},"slug":{"sum"},"title":{"Sum"},
        "solution":{"#include <iostream>\nint main(){int x;std::cin>>x;std::cout<<x;}"},
        "generator":{"#include <iostream>\nint main(int argc,char**v){if(argc!=4)return 1;std::cout<<v[1];}"},
        "commands":{"gen 12 21 32\ngen 99 1 2"},
    }
    post:=func(existing *Entry)error{
        req:=httptest.NewRequest("POST","http://localhost:8000/builder",strings.NewReader(form.Encode()))
        req.Header.Set("Content-Type","application/x-www-form-urlencoded")
        if err:=req.ParseForm();err!=nil{return err}
        _,err:=saveProblem(req,&Page{},existing)
        return err
    }
    if err:=post(nil);err!=nil{t.Fatal(err)}
    e:=catalog[key]
    for i,want:=range []string{"12","99"}{
        path:=[]string{"000001","000002"}[i]
        got,err:=os.ReadFile(filepath.Join(e.Suite,"in",path))
        if err!=nil||string(got)!=want{t.Fatalf("input %s = %q (%v)",path,got,err)}
    }
    var page Page
    if err:=readBuilder(&page,e);err!=nil{t.Fatal(err)}
    form.Set("revision",page.Revision)
    form.Set("solution","broken")
    if err:=post(e);err==nil{t.Fatal("accepted broken edit")}
    form.Set("solution",page.Solution)
    form.Set("editorial","Example\n~~~\nint x;\n~~~")
    if err:=post(e);err!=nil{t.Fatal(err)}
    for _,route:=range []string{"/builder","/editorial","/task"}{
        w:=httptest.NewRecorder()
        serve(w,httptest.NewRequest("GET","http://localhost:8000"+route+"?id="+key,nil))
        if w.Code!=200||!strings.Contains(w.Body.String(),"</html>"){t.Fatalf("%s: %d",route,w.Code)}
    }
}
