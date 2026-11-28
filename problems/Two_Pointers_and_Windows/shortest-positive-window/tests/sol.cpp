#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long target; cin >> n >> target;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    long long sum = 0;
    int l = 0, best = n + 1;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (sum >= target) {
            best = min(best, r - l + 1);
            sum -= a[l++];
        }
    }
    cout << (best <= n ? best : 0) << '\n';
}
