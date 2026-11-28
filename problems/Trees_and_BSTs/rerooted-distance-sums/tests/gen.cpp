#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    
    for(int i=2;i<=n;++i)cout<<(mode==2?i-1:mode==3?1:rnd.next(1,i-1))<<' '<<i<<'\n';
}
