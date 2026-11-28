# Algo Practice

Local C++20 practice on Linux. Install Go 1.22+ and g++, then run from the repository root:

    go run .

Open http://127.0.0.1:8000. Startup reads problem metadata. The first submission builds that problem’s suite when needed. Later submissions reuse it when the samples, hidden inputs, generator arguments, reference, generator, and shared testlib header still match and all numbered input/output pairs exist. Builder saves verify the suite before publishing. Restart after editing problem files outside the builder. Solved marks live in server memory. Submitted programs run as your user; use code you trust.

Each problem lives at problems/SECTION/slug/. meta.json contains the title, statement, sample input/output pairs, editorial and optional manual hidden inputs. tests/sol.cpp computes all expected outputs. Optional tests/gen.cpp prints one additional deterministic input. Generated suites contain paired in/ and out/ files and are rebuilt locally.

Generators can include the vendored upstream [testlib.h](https://github.com/MikeMirzayanov/testlib). Put argument lists in the optional meta.json generatorArgs array; each list runs the generator once. Without this field, gen.cpp runs once without arguments as before.

Commands accept INT_MIN, INT_MAX, LONG_MIN, and LONG_MAX as standalone arguments (Linux signed 32-bit int and 64-bit long). Each expands to a decimal value before the generator runs.


## Building a batch

With the server stopped, use `go run . build Binary_Search/last-occurrence` to force a build of one problem, or `go run . build` for the whole catalog. Each sample is compared with the reference answer. Generated inputs are processed individually. A failed build leaves the previous suite on disk.

For a new drill, set its section, difficulty, intended algorithm, input bounds, output order, and tie rules. Supply hand-checked samples and deterministic generator commands for boundary, random, and maximum-size inputs. Compare the reference against a simpler independent solver on small cases before publishing. A successful suite build alone cannot establish that the reference algorithm is correct.

## Practice workspace

Open a task’s **Workspace** to paste C++20 or import a file. Load a public sample or type your own standard input. **Run case** (Ctrl+Enter in the editor) shows stdout, diagnostics and execution time. Enable token comparison to check your expected answer, including empty output. **Submit to judge** runs the official suite and can mark the problem solved for this server session.

Enter carries forward indentation. After an opening brace it adds four spaces, and between braces it places the closing brace on its own line. These keys also work in the builder’s reference and generator editors. In editorials, use a line beginning with `## ` for a section heading and standalone `~~~` lines around C++.
