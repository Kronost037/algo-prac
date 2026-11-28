#include <bits/stdc++.h>
using namespace std;

using Summary=pair<int,int>;
Summary mergeSummary(Summary a,Summary b) {
    if(a.first<b.first) return a;
    if(b.first<a.first) return b;
    return {a.first,a.second+b.second};
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    int size=bit_ceil(unsigned(n));
    const Summary empty{INT_MAX,0};
    vector<Summary>t(2*size,empty);
    for(int i=0;i<n;++i) {
        int x; cin>>x; t[size+i]={x,1};
    }
    for(int i=size-1;i>0;--i) t[i]=mergeSummary(t[2*i],t[2*i+1]);
    while(q--) {
        string op; int l,r; cin>>op>>l>>r;
        if(op=="SET") {
            int i=size+l-1;
            t[i]={r,1};
            while((i/=2)>0) t[i]=mergeSummary(t[2*i],t[2*i+1]);
        } else {
            Summary ans=empty;
            for(l+=size-1,r+=size;l<r;l/=2,r/=2) {
                if(l%2) ans=mergeSummary(ans,t[l++]);
                if(r%2) ans=mergeSummary(ans,t[--r]);
            }
            cout<<ans.first<<' '<<ans.second<<'\n';
        }
    }
}
