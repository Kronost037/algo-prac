#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==2?n:mode==3?1:max(1,n/2);
    cout<<n<<' '<<k<<'\n';
    for(int i=0;i<n;++i) {
        int x=mode==2?-1000000000:mode==3?i-1000000000:rnd.next(-100,100);
        cout<<x<<(i+1==n?'\n':' ');
    }
}
