#include <bits/stdc++.h>
using namespace std;

int bound(const vector<int>& a, int x, bool upper) {
    int l = 0, r = a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < x || (upper && a[mid] == x)) l = mid + 1;
        else r = mid;
    }
    return l;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    while (q--) {
        string type; int x; cin >> type >> x;
        int lo = bound(a, x, false), hi = bound(a, x, true);
        if (type == "COUNT") cout << hi - lo;
        else if (lo == hi) cout << 0;
        else cout << (type == "FIRST" ? lo + 1 : hi);
        cout << '\n';
    }
}
