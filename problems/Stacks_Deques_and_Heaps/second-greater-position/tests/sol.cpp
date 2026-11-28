#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n), answer(n), waitingFirst, waitingSecond, moved;
    for (int& x : a) std::cin >> x;
    for (int i = 0; i < n; ++i) {
        while (!waitingSecond.empty() && a[waitingSecond.back()] < a[i]) {
            answer[waitingSecond.back()] = i + 1;
            waitingSecond.pop_back();
        }
        while (!waitingFirst.empty() && a[waitingFirst.back()] < a[i]) {
            moved.push_back(waitingFirst.back());
            waitingFirst.pop_back();
        }
        while (!moved.empty()) {
            waitingSecond.push_back(moved.back());
            moved.pop_back();
        }
        waitingFirst.push_back(i);
    }
    for (int i = 0; i < n; ++i) std::cout << answer[i] << (i + 1 == n ? '\n' : ' ');
}
