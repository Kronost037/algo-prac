#include "testlib.h"
#include <climits>
#include <iostream>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    if (argc == 1) {
        std::cout << rnd.next(INT_MIN, INT_MAX) << ' ' << rnd.next(INT_MIN, INT_MAX) << '\n';
        return 0;
    }
    ensuref(argc == 3, "expected two signed 32-bit operands");
    const int a = opt<int>(1);
    const int b = opt<int>(2);
    std::cout << a << ' ' << b << '\n';
}
