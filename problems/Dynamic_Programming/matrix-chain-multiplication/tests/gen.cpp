#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<=n;++i) cout<<(mode==2?100000:mode==3?(i==n/2?1:100000):rnd.next(1,100))<<(i==n?'\n':' ');
}
