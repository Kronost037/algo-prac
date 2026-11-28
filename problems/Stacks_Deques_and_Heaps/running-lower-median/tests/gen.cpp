#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';

    for (int i=0;i<n;++i) {
        int x=mode==0?-7:mode==1?rnd.next(-10,10):mode==2?-i:mode==3?i:i%2?1000000000:-1000000000;
        cout<<x<<(i+1==n?'\n':' ');
    }
}
