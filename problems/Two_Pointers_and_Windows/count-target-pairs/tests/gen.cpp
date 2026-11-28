#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    long long target=mode==3?2999999999LL:0;
    cout<<n<<' '<<target<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0 || mode==2 ? 0 : mode==3 ? rnd.next(500000000,1000000000) : rnd.next(-9,9);
        cout<<x<<(i+1==n?'\n':' ');
    }
}
