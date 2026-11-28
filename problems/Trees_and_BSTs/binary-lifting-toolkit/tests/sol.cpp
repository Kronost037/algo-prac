#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;++i){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
    int levels=bit_width(unsigned(n));
    vector<vector<int>> up(levels,vector<int>(n+1));
    vector<int> depth(n+1),order{1};
    for(size_t i=0;i<order.size();++i){
        int v=order[i];
        for(int u:g[v])if(u!=up[0][v]){
            up[0][u]=v;depth[u]=depth[v]+1;order.push_back(u);
        }
    }
    for(int j=1;j<levels;++j)for(int v=1;v<=n;++v)up[j][v]=up[j-1][up[j-1][v]];
    auto lift=[&](int v,int k){
        for(int j=0;j<levels;++j)if(k>>j&1)v=up[j][v];
        return v;
    };
    auto lca=[&](int u,int v){
        if(depth[u]<depth[v])swap(u,v);
        u=lift(u,depth[u]-depth[v]);
        if(u==v)return u;
        for(int j=levels-1;j>=0;--j)if(up[j][u]!=up[j][v]){u=up[j][u];v=up[j][v];}
        return up[0][u];
    };
    while(q--){
        string op;int u,v;cin>>op>>u>>v;
        if(op=="ANC"){cout<<lift(u,v)<<'\n';continue;}
        int w=lca(u,v),left=depth[u]-depth[w],distance=left+depth[v]-depth[w];
        if(op=="LCA")cout<<w<<'\n';
        else if(op=="DIST")cout<<distance<<'\n';
        else{int k;cin>>k;cout<<(k>distance?0:k<=left?lift(u,k):lift(v,distance-k))<<'\n';}
    }
}
