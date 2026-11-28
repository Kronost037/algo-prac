#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q,s;cin>>n>>m>>q>>s;
    vector<vector<pair<int,int>>>g(n+1);
    while(m--){int u,v,w;cin>>u>>v>>w;g[u].emplace_back(v,w);}
    const long long inf=LLONG_MAX/4;
    using State=tuple<long long,int,int>;
    priority_queue<State,vector<State>,greater<State>>open;
    vector<array<long long,2>>d(n+1,{inf,inf});
    auto relax=[&](int v,int used,long long cost){
        if(cost<d[v][used]){d[v][used]=cost;open.emplace(cost,v,used);}
    };
    relax(s,0,0);
    while(!open.empty()){
        auto [cost,v,used]=open.top();open.pop();
        if(cost!=d[v][used])continue;
        for(auto [u,w]:g[v]){
            relax(u,used,cost+w);
            if(!used)relax(u,1,cost+w/2);
        }
    }
    while(q--){int v;cin>>v;long long result=min(d[v][0],d[v][1]);cout<<(result==inf?-1:result)<<'\n';}
}
