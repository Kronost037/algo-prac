#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=mode==0?0:mode==1?80:200000;
    cout<<n<<' '<<q<<'\n';
    for (int i=1;i<=n;++i) cout<<rnd.next(-9,9)<<(i==n?'\n':' ');
    for (int i=0;i<q;++i) {
        int l=mode==2?1:rnd.next(1,n), r=mode==2?n:rnd.next(l,n);
        cout<<l<<' '<<r<<' '<<rnd.next(-1000000,1000000)<<' '<<(mode==2?1000000:rnd.next(-1000000,1000000))<<'\n';
    }
}
