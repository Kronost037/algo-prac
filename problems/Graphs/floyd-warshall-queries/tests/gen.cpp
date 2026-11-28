#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?91:200000;
    int m=mode==0?0:mode==1?3*n:mode==2?n*(n-1)/2:n-1;
    cout<<n<<' '<<m<<' '<<q<<'\n';
    vector<int>p(n+1);
    for(int i=1;i<=n;++i)p[i]=rnd.next(-100,100);
    if(mode==2){
        for(int u=1;u<=n;++u)for(int v=u+1;v<=n;++v)
            cout<<u<<' '<<v<<' '<<v-u+p[v]-p[u]<<'\n';
    }else if(mode==3){
        for(int u=1;u<n;++u)cout<<u<<' '<<u+1<<" -1000000000\n";
    }else for(int i=0;i<m;++i){
        int u=rnd.next(1,n),v=rnd.next(1,n);
        cout<<u<<' '<<v<<' '<<rnd.next(0,100)+p[v]-p[u]<<'\n';
    }
    for(int i=0;i<q;++i)cout<<rnd.next(1,n)<<' '<<rnd.next(1,n)<<'\n';
}
