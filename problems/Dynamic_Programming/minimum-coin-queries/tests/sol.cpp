#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>coins(n),targets(q);
    for(int& x:coins) cin>>x;
    for(int& t:targets) cin>>t;
    int top=*max_element(targets.begin(),targets.end()),inf=top+1;
    vector<int>dp(top+1,inf);
    dp[0]=0;
    for(int s=1;s<=top;++s)
        for(int x:coins) if(x<=s) dp[s]=min(dp[s],dp[s-x]+1);
    for(int t:targets) cout<<(dp[t]==inf?-1:dp[t])<<'\n';
}
