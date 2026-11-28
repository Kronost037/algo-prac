#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==0?-1:mode==1?rnd.next(-20,20):mode==2?i:mode==3?-i:i%3)<<(i+1==n?'\n':' ');
}
