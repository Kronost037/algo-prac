#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=opt<int>(3);
    cout<<n<<' '<<m<<'\n';
    for(int r=0;r<n;++r) {
        string row(m,'.');
        for(int c=0;c<m;++c) if(mode==0 || (mode==1&&rnd.next(0,3)==0) || (mode==3&&r+c==n/2)) row[c]='#';
        cout<<row<<'\n';
    }
}
