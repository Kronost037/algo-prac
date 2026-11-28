#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,q; cin >> n >> m >> q;
    vector<vector<long long>> p(n+1,vector<long long>(m+1));
    for (int r=1;r<=n;++r) for (int c=1;c<=m;++c) {
        long long x; cin>>x;
        p[r][c]=x+p[r-1][c]+p[r][c-1]-p[r-1][c-1];
    }
    while (q--) {
        int a,b,c,d; cin>>a>>b>>c>>d;
        cout<<p[c][d]-p[a-1][d]-p[c][b-1]+p[a-1][b-1]<<'\n';
    }
}
