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

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;DSU d(n);
    while(q--){
        string op;int u;cin>>op>>u;
        if(op=="SIZE")cout<<d.count(u)<<'\n';
        else{int v;cin>>v;if(op=="UNION")d.unite(u,v);else cout<<(d.find(u)==d.find(v)?"YES":"NO")<<'\n';}
    }
}
