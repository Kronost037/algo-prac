#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q,s;cin>>n>>m>>q>>s;
    vector<vector<pair<int,int>>>g(n+1);
    while(m--){int u,v,w;cin>>u>>v>>w;g[u].emplace_back(v,w);}
    const long long inf=LLONG_MAX/4;
    using State=pair<long long,int>;
    priority_queue<State,vector<State>,greater<State>>open;
    vector<long long>d(n+1,inf);
    d[s]=0;
    open.emplace(0,s);
    while(!open.empty()){
        auto [cost,v]=open.top();open.pop();
        if(cost!=d[v])continue;
        for(auto [u,w]:g[v])if(cost+w<d[u]){
            d[u]=cost+w;
            open.emplace(d[u],u);
        }
    }
    while(q--){
        int v;cin>>v;
        cout<<(d[v]==inf?-1:d[v])<<'\n';
    }
}
