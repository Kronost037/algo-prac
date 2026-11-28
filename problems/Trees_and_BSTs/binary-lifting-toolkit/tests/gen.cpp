#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?101:100000;
    cout<<n<<' '<<q<<'\n';
    
    for(int i=2;i<=n;++i)cout<<(mode==2?i-1:mode==3?1:rnd.next(1,i-1))<<' '<<i<<'\n';

    for(int i=0;i<q;++i){
        int u=rnd.next(1,n),v=rnd.next(1,n);
        if(i%4==0)cout<<"ANC "<<u<<' '<<rnd.next(0,n)<<'\n';
        if(i%4==1)cout<<"LCA "<<u<<' '<<v<<'\n';
        if(i%4==2)cout<<"DIST "<<u<<' '<<v<<'\n';
        if(i%4==3)cout<<"PATH "<<u<<' '<<v<<' '<<(i%3?rnd.next(0,n):0)<<'\n';
    }
}
