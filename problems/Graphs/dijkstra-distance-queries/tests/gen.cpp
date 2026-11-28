#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?91:200000;
    int m=mode==0?0:mode==1?3*n:n-1;
    cout<<n<<' '<<m<<' '<<q<<" 1\n";
    for(int i=0;i<m;++i){
        int u=mode==1?rnd.next(1,n):i+1,v=mode==1?rnd.next(1,n):i+2;
        int weight=mode==2?1000000000:mode==3?i%30:rnd.next(0,50);
        cout<<u<<' '<<v<<' '<<weight<<'\n';
    }
    for(int i=0;i<q;++i)cout<<(i%3==0?n:i%3==1?1:rnd.next(1,n))<<'\n';
}
