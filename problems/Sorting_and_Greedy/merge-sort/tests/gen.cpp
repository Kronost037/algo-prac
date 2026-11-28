#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0?1:mode==1?rnd.next(-30,30):mode==2?n-i:mode==3?i:0;
        cout<<x<<(i+1==n?'\n':' ');
    }
}
