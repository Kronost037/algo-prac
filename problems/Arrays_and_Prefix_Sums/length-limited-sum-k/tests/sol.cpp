#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, low, high; long long target;
    cin >> n >> low >> high >> target;
    vector<long long> prefix(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x; cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }
    auto keys = prefix;
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());
    vector<int> rank(n + 1), count(keys.size());
    for (int i = 0; i <= n; ++i)
        rank[i] = lower_bound(keys.begin(), keys.end(), prefix[i]) - keys.begin();
    long long answer = 0;
    for (int r = low; r <= n; ++r) {
        ++count[rank[r - low]];
        if (r > high) --count[rank[r - high - 1]];
        auto it = lower_bound(keys.begin(), keys.end(), prefix[r] - target);
        if (it != keys.end() && *it == prefix[r] - target) answer += count[it - keys.begin()];
    }
    cout << answer << '\n';
}
