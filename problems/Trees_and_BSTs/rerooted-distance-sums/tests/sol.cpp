#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;++i){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
    vector<int>parent(n+1),depth(n+1),size(n+1,1),order{1};
    vector<long long>answer(n+1);
    for(size_t i=0;i<order.size();++i){
        int v=order[i];answer[1]+=depth[v];
        for(int u:g[v])if(u!=parent[v]){parent[u]=v;depth[u]=depth[v]+1;order.push_back(u);}
    }
    for(int i=n-1;i>0;--i)size[parent[order[i]]]+=size[order[i]];
    for(int i=1;i<n;++i){int v=order[i];answer[v]=answer[parent[v]]+n-2LL*size[v];}
    for(int i=1;i<=n;++i)cout<<answer[i]<<(i==n?'\n':' ');
}
