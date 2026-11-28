#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    vector<string>a(n);for(auto& s:a)cin>>s;
    vector<int>d(n*m,-1),queue;
    for(int r=0;r<n;++r)for(int c=0;c<m;++c)if(a[r][c]=='S'){int v=r*m+c;d[v]=0;queue.push_back(v);}
    const int dr[]={1,-1,0,0},dc[]={0,0,1,-1};
    for(size_t i=0;i<queue.size();++i){
        int v=queue[i],r=v/m,c=v%m;
        for(int k=0;k<4;++k){
            int x=r+dr[k],y=c+dc[k];
            if(x<0||x>=n||y<0||y>=m||a[x][y]=='#'||d[x*m+y]>=0)continue;
            d[x*m+y]=d[v]+1;queue.push_back(x*m+y);
        }
    }
    while(q--){int r,c;cin>>r>>c;cout<<d[(r-1)*m+c-1]<<'\n';}
}
