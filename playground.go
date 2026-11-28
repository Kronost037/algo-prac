package main

import (
	"context"
	"errors"
	"os"
	"time"
)

type Trial struct {
	Status string
	Output string
	Diagnostics string
	Milliseconds int64
}

// A trial runs only the author's input. It has no catalog or suite dependency.
func tryInput(code, input, expected string, compare bool) (Trial, error) {
	dir, err := os.MkdirTemp("", "practice-trial-")
	if err != nil {
		return Trial{}, err
	}
	defer os.RemoveAll(dir)
	if err := os.WriteFile(dir+"/main.cpp", []byte(code), 0600); err != nil {
		return Trial{}, err
	}
	if err := compile(dir, "main.cpp", "main"); err != nil {
		return Trial{Status: "Compilation failed", Diagnostics: err.Error()}, nil
	}
	start := time.Now()
	out, diagnostics, err := execute(dir, input, 2*time.Second, "./main")
	result := Trial{Output: out, Diagnostics: diagnostics, Milliseconds: time.Since(start).Milliseconds()}
	switch {
	case errors.Is(err, context.DeadlineExceeded):
		result.Status = "Time limit exceeded"
	case err != nil:
		result.Status = "Runtime or output error"
		result.Diagnostics += "\n" + err.Error()
	case compare && !same(out, expected):
		result.Status = "Output differs"
	case compare:
		result.Status = "Output matches"
	default:
		result.Status = "Finished"
	}
	return result, nil
}
