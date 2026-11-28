#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=mode==0?0:mode==1?3*n:n-1;
    cout<<n<<' '<<m<<'\n';
    for(int i=0;i<m;++i){
        int u=mode==1?rnd.next(1,n):i+1,v=mode==1?rnd.next(1,n):i+2;
        if(mode==3 && i%7==0)v=u;
        cout<<u<<' '<<v<<' '<<(mode==2?-1000000000:mode==3?1000000000:rnd.next(-100,100))<<'\n';
    }
}
