#include "testlib.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    const std::string mode = opt<std::string>(1);
    const int n = opt<int>(2);
    std::vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        if (mode == "increasing") values[i] = i;
        else if (mode == "decreasing") values[i] = n - i;
        else if (mode == "plateau") values[i] = i >= n - 2 ? i : 0;
        else if (mode == "alternating") values[i] = i % 2 ? 1000000000 : -1000000000;
        else if (mode == "random") values[i] = rnd.next(-5, 5);
    }
    std::cout << n << "\n";
    for (int i = 0; i < n; ++i)
        std::cout << values[i] << (i + 1 == n ? '\n' : ' ');
}
