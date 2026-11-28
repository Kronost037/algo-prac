#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long target; cin >> n >> target;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x; cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }
    deque<int> candidates;
    int best = n + 1;
    for (int r = 0; r <= n; ++r) {
        while (!candidates.empty() && prefix[r] - prefix[candidates.front()] >= target) {
            best = min(best, r - candidates.front());
            candidates.pop_front();
        }
        while (!candidates.empty() && prefix[candidates.back()] >= prefix[r])
            candidates.pop_back();
        candidates.push_back(r);
    }
    cout << (best <= n ? best : 0) << '\n';
}
