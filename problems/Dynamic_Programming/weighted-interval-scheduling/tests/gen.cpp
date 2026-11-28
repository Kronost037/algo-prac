#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i) {
        int l=mode==2?i:mode==3?0:rnd.next(-15,15);
        int r=l+(mode>=2?1:rnd.next(1,15));
        int w=mode==0?-1:mode==1?rnd.next(-20,90):1000000000;
        cout<<l<<' '<<r<<' '<<w<<'\n';
    }
}
