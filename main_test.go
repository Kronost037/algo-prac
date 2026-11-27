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
