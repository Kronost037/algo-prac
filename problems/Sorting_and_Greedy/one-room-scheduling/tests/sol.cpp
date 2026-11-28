#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<pair<int,int>> a(n);
    for (auto& [r,l]:a) cin>>l>>r;
    sort(a.begin(),a.end());
    int end=INT_MIN,answer=0;
    for (auto [r,l]:a) if (l>=end) {
        end=r;
        ++answer;
    }
    cout<<answer<<'\n';
}
