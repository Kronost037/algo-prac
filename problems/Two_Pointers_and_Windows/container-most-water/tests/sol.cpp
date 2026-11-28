#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<long long>a(n);
    for (auto& x:a) cin>>x;
    long long best=0;
    for (int l=0,r=n-1;l<r;) {
        best=max(best,(r-l)*min(a[l],a[r]));
        if (a[l]<=a[r]) ++l;
        else --r;
    }
    cout<<best<<'\n';
}
