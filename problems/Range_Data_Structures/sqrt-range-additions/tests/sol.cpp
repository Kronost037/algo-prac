#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    int size=max(1,int(sqrt(n)));
    vector<long long>a(n),offset((n+size-1)/size);
    for(auto& x:a) cin>>x;
    while(q--) {
        string op;
        int l; cin>>op>>l; --l;
        if(op=="GET") cout<<a[l]+offset[l/size]<<'\n';
        else {
            int r; long long x; cin>>r>>x; --r;
            while(l<=r && l%size) a[l++]+=x;
            while(l+size-1<=r) { offset[l/size]+=x; l+=size; }
            while(l<=r) a[l++]+=x;
        }
    }
}
