#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i){
        uint64_t a=(uint64_t(rnd.next(0,INT_MAX))<<33)|uint64_t(rnd.next(0LL,(1LL<<33)-1));
        uint64_t b=i%7==0?0:UINT64_MAX-a,m=mode==2?UINT64_MAX-i:mode==3?1:uint64_t(rnd.next(1,1000000000));
        if(mode==2 && i%3==0)a=m-1;
        cout<<a<<' '<<b<<' '<<m<<'\n';
    }
}
