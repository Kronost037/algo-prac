#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m; cin>>n>>m;
    constexpr int MOD=1000000007;
    vector<array<int,2>>dp(m+1);
    dp[1][0]=1;
    for(int r=0;r<n;++r) {
        string row; cin>>row;
        for(int c=1;c<=m;++c) {
            int zero=(dp[c][0]+dp[c-1][0])%MOD;
            int one=(dp[c][1]+dp[c-1][1])%MOD;
            dp[c]=row[c-1]=='#'?array<int,2>{0,zero}:array<int,2>{zero,one};
        }
    }
    cout<<(dp[m][0]+dp[m][1])%MOD<<'\n';
}
