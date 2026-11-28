#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int r=0;r<n;++r) {
        string s(n,'.');
        if(mode==1 && r%3==0) s[rnd.next(0,n-1)]='Q';
        if(mode==2 && r<2) s[0]='Q';
        if(mode==3 && r==n-1) s[n/2]='Q';
        cout<<s<<'\n';
    }
}
