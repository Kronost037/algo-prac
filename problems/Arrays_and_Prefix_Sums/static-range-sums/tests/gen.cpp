#include "testlib.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    const std::string mode = opt<std::string>(1);
    const int n = opt<int>(2), q = opt<int>(3);
    std::cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) {
        const int value = mode == "negative" ? -1000000000 :
            mode == "wide" ? 1000000000 : rnd.next(-1000000000, 1000000000);
        std::cout << value << (i + 1 == n ? '\n' : ' ');
    }
    for (int i = 0; i < q; ++i) {
        int l = 1, r = n;
        if (mode == "random") {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        } else if (i % 4 == 1) {
            r = 1;
        } else if (i % 4 == 2) {
            l = n;
        }
        std::cout << l << ' ' << r << '\n';
    }
}
