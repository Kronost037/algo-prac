#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?99:200000;
    cout<<n<<' '<<q<<'\n';
    for (int i=1;i<=n;++i) cout<<(mode==2?1000000000:rnd.next(-100,100))<<(i==n?'\n':' ');
    for (int i=0;i<q;++i) {
        if (i%3!=2) {
            int at=mode==2?1:mode==3?n:rnd.next(1,n);
            cout<<"ADD "<<at<<' '<<(i%2?1000000000:-1000000000)<<'\n';
        } else {
            int l=mode>=2?1:rnd.next(1,n),r=mode>=2?n:rnd.next(l,n);
            cout<<"SUM "<<l<<' '<<r<<'\n';
        }
    }
}
