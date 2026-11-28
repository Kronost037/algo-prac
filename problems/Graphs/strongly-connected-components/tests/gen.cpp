#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=mode==0?0:mode==1?2*n:mode==2?n-1:n;
    int q=n<100?99:200000;cout<<n<<' '<<m<<' '<<q<<'\n';
    for(int i=0;i<m;++i){
        int u=mode>=2?i+1:rnd.next(1,n),v=mode>=2?(i+1)%n+1:rnd.next(1,n);
        cout<<u<<' '<<v<<'\n';
    }

    for(int i=0;i<q;++i){int u=rnd.next(1,n);cout<<u<<' '<<(i%3==0?u:rnd.next(1,n))<<'\n';}
}
