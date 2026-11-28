#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>a(n);
    for (auto& x:a) cin>>x;
    int l=0,r=n-1;
    while (l<r) {
        int m=l+(r-l)/2;
        if (a[m]>a[r]) l=m+1;
        else r=m;
    }
    int pivot=l;
    while (q--) {
        int x; cin>>x;
        l=0; r=n;
        while (l<r) {
            int m=l+(r-l)/2;
            if (a[(pivot+m)%n]<x) l=m+1;
            else r=m;
        }
        int at=(pivot+l)%n;
        cout<<(l<n && a[at]==x?at+1:0)<<'\n';
    }
}
