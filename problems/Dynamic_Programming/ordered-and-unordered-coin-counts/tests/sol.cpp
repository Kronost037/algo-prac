#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,t; cin>>n>>t;
    vector<int>c(n),ordered(t+1),unordered(t+1);
    for(int& x:c) cin>>x;
    constexpr int MOD=1000000007;
    auto add=[](int& x,int y){ x+=y; if(x>=MOD) x-=MOD; };
    ordered[0]=unordered[0]=1;
    for(int s=1;s<=t;++s) for(int x:c) if(x<=s) add(ordered[s],ordered[s-x]);
    for(int x:c) for(int s=x;s<=t;++s) add(unordered[s],unordered[s-x]);
    cout<<ordered[t]<<' '<<unordered[t]<<'\n';
}
