#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==3?n:mode==1?min(n,3):1;
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) cout<<(mode==3?i:mode==2?0:rnd.next(-5,5))<<(i+1==n?'\n':' ');
}
