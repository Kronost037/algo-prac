#include <bits/stdc++.h>
using namespace std;

struct Frame{int v,parentEdge,next;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<pair<int,int>>>g(n+1);
    for(int i=0;i<m;++i){int u,v;cin>>u>>v;g[u].emplace_back(v,i);g[v].emplace_back(u,i);}
    vector<char>seen(n+1);
    for(int root=1;root<=n;++root)if(!seen[root]){
        vector<Frame>st{{root,-1,0}};seen[root]=1;
        while(!st.empty()){
            auto& f=st.back();
            if(f.next==int(g[f.v].size())){st.pop_back();continue;}
            auto [u,id]=g[f.v][f.next++];
            if(id==f.parentEdge)continue;
            if(seen[u]){cout<<"YES\n";return 0;}
            seen[u]=1;st.push_back({u,id,0});
        }
    }
    cout<<"NO\n";
}
