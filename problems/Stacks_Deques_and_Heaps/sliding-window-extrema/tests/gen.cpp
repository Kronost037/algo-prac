#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==0?1:mode==2?n:n/2+1;
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) cout<<(mode==3?i:mode==4?n-i:rnd.next(-100,100))<<(i+1==n?'\n':' ');
}
