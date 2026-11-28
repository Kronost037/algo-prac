#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<long long,int>> stack;
    long long best = 0;
    for (int i = 0; i <= n; ++i) {
        long long h = 0;
        if (i < n) cin >> h;
        int start = i;
        while (!stack.empty() && stack.back().first > h) {
            auto [height, left] = stack.back();
            stack.pop_back();
            best = max(best, height * (i - left));
            start = left;
        }
        if (stack.empty() || stack.back().first < h) stack.emplace_back(h, start);
    }
    cout << best << '\n';
}
