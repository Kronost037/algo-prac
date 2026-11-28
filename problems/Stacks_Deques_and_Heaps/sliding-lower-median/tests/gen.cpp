#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==0?1:mode==2?n:mode==3?2:mode==4?100001:min(n, n/2+1);
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==3?(i%2?-1000000000:1000000000):mode==4?-i:rnd.next(-5,5);
        cout<<x<<(i+1==n?'\n':' ');
    }
}
