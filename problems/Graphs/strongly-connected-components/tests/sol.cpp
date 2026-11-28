#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;vector<vector<int>>g(n+1),rev(n+1);
    while(m--){int u,v;cin>>u>>v;g[u].push_back(v);rev[v].push_back(u);}
    vector<int>order,id(n+1);
    for(int v=1;v<=n;++v)if(!id[v]){
        vector<pair<int,size_t>>st{{v,0}};id[v]=-1;
        while(!st.empty()){
            auto& [u,i]=st.back();
            if(i==g[u].size()){order.push_back(u);st.pop_back();continue;}
            int w=g[u][i++];
            if(!id[w]){id[w]=-1;st.emplace_back(w,0);}
        }
    }
    for(auto it=order.rbegin();it!=order.rend();++it)if(id[*it]<0){
        int root=*it;vector<int>st{root};id[root]=root;
        while(!st.empty()){
            int v=st.back();st.pop_back();
            for(int u:rev[v])if(id[u]<0){id[u]=root;st.push_back(u);}
        }
    }
    while(q--){int u,v;cin>>u>>v;cout<<(id[u]==id[v]?"YES":"NO")<<'\n';}
}
