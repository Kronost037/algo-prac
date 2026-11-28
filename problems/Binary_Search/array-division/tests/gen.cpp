#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==0?n:mode==1?rnd.next(1,n):mode==2?1:791;
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0?0:mode==1?rnd.next(0,30):mode==2?1000000000:i%3?0:1000000000;
        cout<<x<<(i+1==n?'\n':' ');
    }
}
