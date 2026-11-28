#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=mode<2?50:200000;
    int shift=mode==0?0:mode==1?rnd.next(0,n-1):mode==2?1:n-1;
    cout<<n<<' '<<q<<'\n';
    for (int i=0;i<n;++i) cout<<2*((i+shift)%n)-n<<(i+1==n?'\n':' ');
    for (int i=0;i<q;++i) cout<<2*rnd.next(0,n-1)-n+(i%2)<<'\n';
}
