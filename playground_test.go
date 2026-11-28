package main

import (
	"net/http/httptest"
	"net/url"
	"strings"
	"testing"
)

func TestCustomRunThroughTask(t *testing.T) {
	key := "Playground/custom"
	e := &Entry{Section: "Playground", Slug: "custom", Problem: Problem{Title: "Trial"}}
	catalog[key] = e
	defer delete(catalog, key)
	const echo = "#include <iostream>\nint main(){int n;std::cin>>n;std::cout<<2*n;std::cerr<<\"trace\";}"
	for _, tc := range []struct{ code, expected, status, detail string }{
		{echo, "  42\n", "Output matches", "trace"},
		{echo, "", "Output differs", "<pre>42</pre>"},
		{"int main(){}", "", "Output matches", "(empty)"},
		{"int main(){return 1;}", "", "Runtime or output error", "exit status"},
		{"int main(}", "", "Compilation failed", "error:"},
		{"int main(){for(;;){}}", "", "Time limit exceeded", "ms"},
	} {
		form := url.Values{"action":{"run"}, "code":{tc.code}, "stdin":{"21"}, "compare":{"on"}, "expected":{tc.expected}}
		req := httptest.NewRequest("POST", "http://localhost:8000/task?id="+key, strings.NewReader(form.Encode()))
		req.Header.Set("Origin", "http://localhost:8000")
		req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
		w := httptest.NewRecorder()
		serve(w,req)
		body := w.Body.String()
		if w.Code != 200 || !strings.Contains(body,tc.status) || !strings.Contains(body,tc.detail) || e.Solved || e.Suite != "" {
			t.Fatalf("custom run %q: HTTP %d, body %s",tc.status,w.Code,body)
		}
	}
}
