#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<long long>tree(n+1);
    auto add=[&](int i,long long d) {
        for(;i<=n;i+=i&-i) tree[i]+=d;
    };
    for(int i=1;i<=n;++i) {
        long long f; cin>>f;
        add(i,f);
    }
    int high=bit_floor(unsigned(n));
    while(q--) {
        string op; cin>>op;
        if(op=="ADD") {
            int i; long long d; cin>>i>>d; add(i,d);
        } else {
            long long rank; cin>>rank;
            int before=0;
            for(int step=high;step;step/=2)
                if(before+step<=n && tree[before+step]<rank) {
                    before+=step;
                    rank-=tree[before];
                }
            cout<<(before==n?0:before+1)<<'\n';
        }
    }
}
