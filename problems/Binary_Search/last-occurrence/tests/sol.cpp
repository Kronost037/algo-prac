#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    cin >> n >> t;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    while (t--) {
        int x;
        cin >> x;
        auto it = upper_bound(a.begin(), a.end(), pair{x,n});
        cout << (it != a.begin() && prev(it)->first == x ? prev(it)->second : -1) << '\n';
    }
}
