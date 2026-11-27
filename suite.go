package main

import (
    "crypto/sha256"
    "encoding/json"
    "fmt"
    "os"
    "path/filepath"
    "strings"
)

// Only inputs that affect the generated suite belong in this key.
func suiteKey(e *Entry) (string, int, error) {
    hash := sha256.New()
    config := []any{"suite-v1", e.Samples, e.Hidden, e.GeneratorArgs}
    if err := json.NewEncoder(hash).Encode(config); err != nil { return "", 0, err }
    count := len(e.Samples) + len(e.Hidden)
    for _, file := range []string{"tests/sol.cpp","tests/gen.cpp","lib/testlib.h"} {
        path := filepath.Join(e.Dir,file)
        if file == "lib/testlib.h" { path = file }
        source, err := os.ReadFile(path)
        if file == "tests/gen.cpp" && os.IsNotExist(err) && len(e.GeneratorArgs)==0 { continue }
        if err != nil { return "",0,err }
        fmt.Fprintf(hash,"%s:%x\n", file, sha256.Sum256(source))
        if file == "tests/gen.cpp" { count += max(1,len(e.GeneratorArgs)) }
    }
    return fmt.Sprintf("%x", hash.Sum(nil)),count,nil
}

func completeSuite(dir, key string, count int) bool {
    stamp, err := os.ReadFile(filepath.Join(dir,"fingerprint"))
    if err != nil || string(stamp)!=key || count==0 { return false }
    for _, side := range []string{"in","out"} {
        files,err:=os.ReadDir(filepath.Join(dir,side))
        if err!=nil || len(files)!=count { return false }
        for i,file:=range files {
            if !file.Type().IsRegular() || file.Name()!=fmt.Sprintf("%06d",i+1) { return false }
        }
    }
    return true
}

func prepareSuite(e *Entry, force bool) error {
    key,count,err:=suiteKey(e)
    if err!=nil { return err }
    tests:=filepath.Join(e.Dir,"tests")
    marker:=filepath.Join(tests,"current")
    raw,err:=os.ReadFile(marker)
    if err!=nil && !os.IsNotExist(err) { return err }
    name:=string(raw)
    old:=""
    if strings.HasPrefix(name,"suite-") && filepath.Base(name)==name {
        old=filepath.Join(tests,name)
        if !force && completeSuite(old,key,count) { e.Suite=old;return nil }
    }
    suite,err:=build(e)
    if err!=nil { return err }
    tmp,err:=os.CreateTemp(tests,"current-")
    if err!=nil { os.RemoveAll(suite);return err }
    defer os.Remove(tmp.Name())
    _,err=tmp.WriteString(filepath.Base(suite))
    closeErr:=tmp.Close()
    if err==nil { err=closeErr }
    if err==nil { err=os.Rename(tmp.Name(),marker) }
    if err!=nil { os.RemoveAll(suite);return err }
    e.Suite=suite
    if old!="" { os.RemoveAll(old) }
    return nil
}
