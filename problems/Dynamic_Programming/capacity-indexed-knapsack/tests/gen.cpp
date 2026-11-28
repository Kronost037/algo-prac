#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int w=mode==0?0:mode==1?rnd.next(1,40):100000;
    cout<<n<<' '<<w<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?500:mode==3?100001:rnd.next(1,30))<<' '<<(mode>=2?1000000000:rnd.next(1,25))<<'\n';
}
