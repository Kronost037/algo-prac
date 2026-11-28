#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph(int n,int m){
    vector<vector<int>>g(n+1);
    while(m--){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
    return g;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;auto g=graph(n,m);
    vector<int>id(n+1),sizes{0};
    for(int root=1;root<=n;++root)if(!id[root]){
        int group=sizes.size();sizes.push_back(0);
        vector<int>st{root};id[root]=group;
        while(!st.empty()){
            int v=st.back();st.pop_back();++sizes[group];
            for(int u:g[v])if(!id[u]){id[u]=group;st.push_back(u);}
        }
    }
    while(q--){
        string op;int u;cin>>op>>u;
        if(op=="SIZE")cout<<sizes[id[u]]<<'\n';
        else{int v;cin>>v;cout<<(id[u]==id[v]?"YES":"NO")<<'\n';}
    }
}
