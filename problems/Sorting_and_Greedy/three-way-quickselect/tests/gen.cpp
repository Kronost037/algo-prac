#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==2?n:mode==3?1:max(1,n/2);
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0?42:mode==1?rnd.next(-4,4):mode==2?i:n-i;
        cout<<x<<(i+1==n?'\n':' ');
    }
}
