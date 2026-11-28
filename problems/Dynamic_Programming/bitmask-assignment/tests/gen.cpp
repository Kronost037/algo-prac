#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
        int x=mode==2?(j==n-1-i?-1000000000:1000000000):mode==3?(j?7:-1000000000):rnd.next(-30,40);
        cout<<x<<(j+1==n?'\n':' ');
    }
}
