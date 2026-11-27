#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    ensuref(argc == 3, "expected distribution and seed");
    const std::string mode = argv[1];
    constexpr int n = 200000;
    std::vector<int> values(n);
    for (int& value : values)
        value = 2 * rnd.next(-500000000, 499999999);
    if (mode == "duplicates")
        for (int& value : values) value = rnd.next(-2, 2);
    else if (mode == "sorted")
        std::sort(values.begin(), values.end());
    else if (mode == "reverse")
        std::sort(values.rbegin(), values.rend());
    else
        ensuref(mode == "absent" || mode == "mixed", "unknown distribution");
    std::ios::sync_with_stdio(false);
    std::cout << n << ' ' << n << '\n';
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        int query = values[rnd.next(n)];
        if (mode == "absent" || (mode == "mixed" && i % 2)) ++query;
        std::cout << query << '\n';
    }
}
