# Algo Practice

Local C++20 practice on Linux. Install Go 1.22+ and g++, then run from the repository root:

    go run .

Open http://127.0.0.1:8000. The first launch compiles the bundled reference solution and generator to build the missing suite. Run `go run . build` to regenerate suites after external edits. Solved marks live in server memory. Submitted programs run as your user; use code you trust.

Each problem lives at problems/SECTION/slug/. meta.json contains the title, statement, sample input/output pairs, editorial and optional manual hidden inputs. tests/sol.cpp computes all expected outputs. Optional tests/gen.cpp prints one additional deterministic input. Generated suites contain paired in/ and out/ files and are rebuilt locally.

Generators can include the vendored upstream [testlib.h](https://github.com/MikeMirzayanov/testlib). Put argument lists in the optional meta.json generatorArgs array; each list runs the generator once. Without this field, gen.cpp runs once without arguments as before.

Last Occurrence covers all 120 arrays of length 1–4 over {-1, 0, 1}, with queries for every alphabet value, repeated queries and absent neighbors. Ten hand-written scenarios exercise both integer bounds and singleton hit/miss queries. Ten maximum-size cases use two deterministic seeds for each of five distributions (mixed, absent, duplicate-heavy, sorted and reverse sorted).
