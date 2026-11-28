#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long target; cin >> n >> target;
    vector<long long> period(n);
    for (auto& p : period) cin >> p;
    long long l = 1, r = *min_element(period.begin(), period.end()) * target;
    while (l < r) {
        long long mid = l + (r - l) / 2, made = 0;
        for (long long p : period) {
            made += mid / p;
            if (made >= target) break;
        }
        if (made >= target) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
}
