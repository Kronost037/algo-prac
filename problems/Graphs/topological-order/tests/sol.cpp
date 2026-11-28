#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>>g(n+1);vector<int>incoming(n+1),answer;
    while(m--){int u,v;cin>>u>>v;g[u].push_back(v);++incoming[v];}
    priority_queue<int,vector<int>,greater<int>>open;
    for(int v=1;v<=n;++v)if(!incoming[v])open.push(v);
    while(!open.empty()){
        int v=open.top();open.pop();answer.push_back(v);
        for(int u:g[v])if(!--incoming[u])open.push(u);
    }
    if(int(answer.size())!=n){cout<<"IMPOSSIBLE\n";return 0;}
    for(int i=0;i<n;++i)cout<<answer[i]<<(i+1==n?'\n':' ');
}
