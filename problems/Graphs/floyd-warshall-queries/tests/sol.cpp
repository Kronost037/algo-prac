#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    const long long inf=LLONG_MAX/4;
    vector<vector<long long>>d(n+1,vector<long long>(n+1,inf));
    for(int i=1;i<=n;++i)d[i][i]=0;
    while(m--){int u,v;long long w;cin>>u>>v>>w;d[u][v]=min(d[u][v],w);}
    for(int k=1;k<=n;++k)for(int i=1;i<=n;++i)if(d[i][k]!=inf)
        for(int j=1;j<=n;++j)if(d[k][j]!=inf)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    while(q--){int u,v;cin>>u>>v;if(d[u][v]==inf)cout<<"NONE\n";else cout<<d[u][v]<<'\n';}
}
