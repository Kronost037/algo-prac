#include <bits/stdc++.h>
using namespace std;

class Fenwick{
    vector<long long>t;
public:
    explicit Fenwick(int n):t(n+1){}
    void add(int i,long long x){for(;i<int(t.size());i+=i&-i)t[i]+=x;}
    long long sum(int i)const{long long s=0;for(;i;i-=i&-i)s+=t[i];return s;}
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<int>a(n+1);
    for(int i=1;i<=n;++i)cin>>a[i];
    vector<vector<int>>g(n+1);
    for(int i=1;i<n;++i){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
    vector<int>in(n+1),out(n+1);
    vector<pair<int,int>> stack{{1,0}};
    int timer=0;
    while(!stack.empty()){
        auto [v,p]=stack.back();stack.pop_back();
        if(v<0){out[-v]=timer;continue;}
        in[v]=++timer;stack.emplace_back(-v,p);
        for(int u:g[v])if(u!=p)stack.emplace_back(u,v);
    }
    Fenwick slope(n),offset(n);
    auto point=[&](int i,long long x){slope.add(i,x);offset.add(i,(i-1)*x);};
    auto add=[&](int l,int r,long long x){point(l,x);point(r+1,-x);};
    auto prefix=[&](int i){return i*slope.sum(i)-offset.sum(i);};
    for(int v=1;v<=n;++v)add(in[v],in[v],a[v]);
    while(q--){
        string op;int u;cin>>op>>u;
        if(op=="ADD"){int x;cin>>x;add(in[u],out[u],x);}
        else cout<<prefix(out[u])-prefix(in[u]-1)<<'\n';
    }
}
