#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph(int n,int m){
    vector<vector<int>>g(n+1);
    while(m--){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
    return g;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;cin>>n>>m;auto g=graph(n,m);
    vector<int>color(n+1);
    for(int root=1;root<=n;++root)if(!color[root]){
        vector<int>q{root};color[root]=1;
        for(size_t i=0;i<q.size();++i)for(int u:g[q[i]]){
            if(color[u]==color[q[i]]){cout<<"IMPOSSIBLE\n";return 0;}
            if(!color[u]){color[u]=3-color[q[i]];q.push_back(u);}
        }
    }
    for(int v=1;v<=n;++v)cout<<color[v]<<(v==n?'\n':' ');
}
