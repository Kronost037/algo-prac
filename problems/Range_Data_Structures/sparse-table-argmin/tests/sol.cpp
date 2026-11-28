#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>lg(n+1);
    for (int i=2;i<=n;++i) lg[i]=lg[i/2]+1;
    vector<vector<pair<int,int>>>table(lg[n]+1,vector<pair<int,int>>(n));
    for (int i=0;i<n;++i) {
        cin>>table[0][i].first;
        table[0][i].second=i+1;
    }
    for (int k=1;k<=lg[n];++k)
        for (int i=0;i+(1<<k)<=n;++i)
            table[k][i]=min(table[k-1][i],table[k-1][i+(1<<(k-1))]);
    while (q--) {
        int l,r; cin>>l>>r;
        int k=lg[r-l+1];
        auto [value,position]=min(table[k][l-1],table[k][r-(1<<k)]);
        cout<<value<<' '<<position<<'\n';
    }
}
