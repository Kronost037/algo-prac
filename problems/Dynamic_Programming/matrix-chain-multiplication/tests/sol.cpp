#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin>>n;
    vector<long long>d(n+1);
    for(auto& x:d) cin>>x;
    vector<vector<long long>>dp(n,vector<long long>(n));
    for(int len=2;len<=n;++len) for(int l=0;l+len<=n;++l) {
        int r=l+len-1;
        dp[l][r]=LLONG_MAX;
        for(int k=l;k<r;++k)
            dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]+d[l]*d[k+1]*d[r+1]);
    }
    cout<<dp[0][n-1]<<'\n';
}
