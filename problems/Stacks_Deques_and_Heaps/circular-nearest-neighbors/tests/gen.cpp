#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=min(200000,4*n);
    cout<<n<<' '<<q<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0?0:mode==1?rnd.next(-4,4):mode==2?(i==0?1:0):i;
        cout<<x<<(i+1==n?'\n':' ');
    }
    for (int i=0;i<q;++i) cout<<i%4+1<<' '<<(i/4+i%4*(n/4))%n+1<<'\n';
}
