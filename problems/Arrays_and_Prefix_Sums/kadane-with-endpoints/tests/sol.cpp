#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    long long ending = 0, best = LLONG_MIN;
    int start = 1, left = 1, right = 1;
    for (int i = 1; i <= n; ++i) {
        long long x; cin >> x;
        if (ending <= 0) {
            ending = 0;
            start = i;
        }
        ending += x;
        int len = i - start, bestLen = right - left;
        if (ending > best || (ending == best &&
            (len < bestLen || (len == bestLen && start < left)))) {
            best = ending;
            left = start;
            right = i;
        }
    }
    cout << best << ' ' << left << ' ' << right << '\n';
}
