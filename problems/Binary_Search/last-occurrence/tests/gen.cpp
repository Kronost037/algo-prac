#include <iostream>
#include <random>
int main() {
    constexpr int n = 200000;
    std::mt19937 rng(37);
    std::cout << n << ' ' << n << '\n';
    for (int i = 0; i < n; ++i)
        std::cout << 2 * (rng() % n) << ' ';
    std::cout << '\n';
    for (int i = 0; i < n; ++i)
        std::cout << rng() % (2*n) << '\n';
}
