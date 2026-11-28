#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    const int edge[]={1,524288,1000000,999983,999950,720720};
    for(int i=0;i<n;++i)cout<<(i%2?"DIV ":"FACT ")<<(mode==2?edge[(i/2)%6]:mode==3?rnd.next(900000,1000000):rnd.next(1,200))<<'\n';
}
