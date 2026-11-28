#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=1;i<=n;++i) {
        int l=mode==2?i+1:2*i,r=mode==2?0:2*i+1;
        if(l>n)l=0;
        if(r>n)r=0;
        int value=mode==0?-5:mode==2?1000000000:mode==3?i:rnd.next(-20,20);
        cout<<value<<' '<<l<<' '<<r<<'\n';
    }
}
