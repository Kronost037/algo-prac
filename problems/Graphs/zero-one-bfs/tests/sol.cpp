#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q,s;cin>>n>>m>>q>>s;
    vector<vector<pair<int,int>>>g(n+1);
    while(m--){int u,v,w;cin>>u>>v>>w;g[u].emplace_back(v,w);}
    const long long inf=LLONG_MAX/4;
    vector<long long>d(n+1,inf);
    deque<pair<long long,int>>open;
    open.emplace_back(0,s);d[s]=0;
    while(!open.empty()){
        auto [cost,v]=open.front();open.pop_front();
        if(cost!=d[v])continue;
        for(auto [u,w]:g[v]){
            if(cost+w>=d[u])continue;
            d[u]=cost+w;
            if(w)open.emplace_back(d[u],u);else open.emplace_front(d[u],u);
        }
    }
    while(q--){int v;cin>>v;cout<<(d[v]==inf?-1:d[v])<<'\n';}
}
