#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<pair<int,int>> a(n);
    for (auto& [r,l]:a) cin>>l>>r;
    sort(a.begin(),a.end());
    multiset<int> ends;
    for (int i=0;i<k;++i) ends.insert(INT_MIN);
    int answer=0;
    for (auto [r,l]:a) {
        auto it=ends.upper_bound(l);
        if (it==ends.begin()) continue;
        ends.erase(prev(it));
        ends.insert(r);
        ++answer;
    }
    cout<<answer<<'\n';
}
