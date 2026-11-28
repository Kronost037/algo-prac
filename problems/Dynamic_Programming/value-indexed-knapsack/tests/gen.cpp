#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    long long w=mode==0?0:mode==1?rnd.next(1,40):mode==2?50000000000000LL:999999999999LL;
    cout<<n<<' '<<w<<'\n';
    for(int i=0;i<n;++i) cout<<(mode>=2?1000000000000LL:rnd.next(1,30))<<' '<<(mode>=2?1000:rnd.next(1,25))<<'\n';
}
