#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,w; cin>>n>>w;
    vector<long long>dp(w+1);
    while(n--) {
        int weight; long long value; cin>>weight>>value;
        for(int c=w;c>=weight;--c) dp[c]=max(dp[c],dp[c-weight]+value);
    }
    cout<<dp[w]<<'\n';
}
