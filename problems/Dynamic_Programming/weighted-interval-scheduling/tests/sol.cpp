#include <bits/stdc++.h>
using namespace std;

struct Screening { int start,end,reward; };
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<Screening>a(n);
    for(auto& item:a) cin>>item.start>>item.end>>item.reward;
    sort(a.begin(),a.end(),[](auto x,auto y){return x.end<y.end;});
    vector<int> ends;
    for(auto item:a) ends.push_back(item.end);
    vector<long long>best(n+1);
    for(int i=0;i<n;++i) {
        int p=upper_bound(ends.begin(),ends.begin()+i,a[i].start)-ends.begin();
        best[i+1]=max(best[i],best[p]+a[i].reward);
    }
    cout<<best[n]<<'\n';
}
