#include "testlib.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    const std::string mode = opt<std::string>(1);
    const int n = opt<int>(2);
    ensuref(1 <= n && n <= 200000, "length out of bounds");
    std::string s(n, 'a');
    if (mode == "alphabet") {
        for (int i = 0; i < n; ++i) s[i] = char('a' + i % 26);
    } else if (mode == "alternating" || mode == "broken") {
        for (int i = 1; i < n; i += 2) s[i] = 'b';
        if (mode == "broken") s[n - 1] = 'z';
    } else if (mode == "random") {
        for (char& c : s) c = char('a' + rnd.next(26));
    } else ensuref(mode == "uniform", "unknown distribution");
    std::cout << s << '\n';
}

