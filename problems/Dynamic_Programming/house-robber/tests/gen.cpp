#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==0?-99:mode==1?rnd.next(-12,12):mode==2?1000000000:i==0||i==n-1?50:-10)<<(i+1==n?'\n':' ');
}
