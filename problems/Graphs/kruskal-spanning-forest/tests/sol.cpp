#include <bits/stdc++.h>
using namespace std;

class DSU{
    vector<int>parent,size;
public:
    explicit DSU(int n):parent(n+1),size(n+1,1){iota(parent.begin(),parent.end(),0);}
    int find(int v){
        while(parent[v]!=v){parent[v]=parent[parent[v]];v=parent[v];}
        return v;
    }
    int count(int v){return size[find(v)];}
    bool unite(int u,int v){
        u=find(u);v=find(v);
        if(u==v)return false;
        if(size[u]<size[v])swap(u,v);
        size[u]+=size[v];parent[v]=u;return true;
    }
};

struct Edge{int u,v,w;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<Edge>edges(m);
    for(auto& e:edges)cin>>e.u>>e.v>>e.w;
    sort(edges.begin(),edges.end(),[](Edge a,Edge b){return a.w<b.w;});
    DSU d(n);long long total=0;
    for(auto e:edges)if(d.unite(e.u,e.v)){--n;total+=e.w;}
    cout<<total<<' '<<n<<'\n';
}
