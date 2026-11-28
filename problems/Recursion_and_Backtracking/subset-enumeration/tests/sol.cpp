#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<int>a(n);
    for (int& x:a) cin>>x;
    for (unsigned mask=0;mask<(1u<<n);++mask) {
        cout<<popcount(mask);
        for (int i=0;i<n;++i) if (mask>>i&1u) cout<<' '<<a[i];
        cout<<'\n';
    }
}
