#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=opt<int>(3);
    cout<<n<<' '<<k<<'\n';

    for (int i=0;i<n;++i) {
        int l,r;
        if (mode==0) { l=0; r=1; }
        else if (mode==2) { l=i; r=i+1; }
        else if (mode==3) { l=-1000000000+i; r=1000000000-i; }
        else { l=rnd.next(-20,20); r=l+rnd.next(1,20); }
        cout<<l<<' '<<r<<'\n';
    }
}
