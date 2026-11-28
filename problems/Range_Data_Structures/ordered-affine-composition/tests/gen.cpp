#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?135:100000, mod=mode==0?1:mode==1?97:1000000007;
    auto coefficient=[&] { return rnd.next(0,mod-1); };
    cout<<n<<' '<<q<<' '<<mod<<'\n';
    for (int i=0;i<n;++i) cout<<coefficient()<<' '<<coefficient()<<'\n';
    for (int i=0;i<q;++i) {
        if (i%5==0) cout<<"SET "<<rnd.next(1,n)<<' '<<coefficient()<<' '<<coefficient()<<'\n';
        else {
            int l=mode==2?1:rnd.next(1,n),r=mode==2?n:rnd.next(l,n);
            cout<<"APPLY "<<l<<' '<<r<<' '<<coefficient()<<'\n';
        }
    }
}
