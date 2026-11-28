package main

import (
	"net/http"
	"net/http/httptest"
	"os/exec"
	"path/filepath"
	"testing"
)

func TestWorkspaceBrowser(t *testing.T) {
	for _, tool := range []string{"google-chrome", "chromedriver", "python3"} {
		if _, err := exec.LookPath(tool); err != nil {
			t.Skipf("browser smoke test requires %s", tool)
		}
	}
	dir, err := filepath.Abs("problems/Binary_Search/last-occurrence")
	if err != nil {
		t.Fatal(err)
	}
	if err := load(dir, false); err != nil {
		t.Fatal(err)
	}
	// Map this ephemeral loopback origin onto the application's fixed local port.
	server := httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if r.Header.Get("Origin") == "http://"+r.Host {
			r.Header.Set("Origin", "http://localhost:8000")
		}
		r.Host = "localhost:8000"
		serve(w, r)
	}))
	defer server.Close()
	cmd := exec.Command("python3", "testdata/workspace_browser.py", server.URL)
	if output, err := cmd.CombinedOutput(); err != nil {
		t.Fatalf("browser smoke test: %v\n%s", err, output)
	}
}
