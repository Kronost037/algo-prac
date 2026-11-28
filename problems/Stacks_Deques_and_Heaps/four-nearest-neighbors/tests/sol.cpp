#include <array>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::array<std::vector<int>, 4> answer;
    for (int type = 0; type < 4; ++type) {
        answer[type].resize(n + 1);
        const bool right = type < 2, greater = type % 2 == 0;
        std::vector<int> stack;
        for (int i = right ? n : 1; i >= 1 && i <= n; i += right ? -1 : 1) {
            while (!stack.empty() &&
                   (greater ? a[stack.back()] <= a[i] : a[stack.back()] >= a[i]))
                stack.pop_back();
            if (!stack.empty()) answer[type][i] = stack.back();
            stack.push_back(i);
        }
    }
    while (q--) {
        int type, i;
        std::cin >> type >> i;
        std::cout << answer[type - 1][i] << '\n';
    }
}
