#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<long long> a(n+1),slope(n+2),intercept(n+2);
    for (int i=1;i<=n;++i) cin>>a[i];
    while (q--) {
        int l,r; long long x,d; cin>>l>>r>>x>>d;
        long long b=x-l*d;
        slope[l]+=d; slope[r+1]-=d;
        intercept[l]+=b; intercept[r+1]-=b;
    }
    long long m=0,b=0;
    for (int i=1;i<=n;++i) {
        m+=slope[i]; b+=intercept[i];
        cout<<a[i]+i*m+b<<(i==n?'\n':' ');
    }
}
