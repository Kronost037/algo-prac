#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?80:200000;
    cout<<n<<' '<<q<<'\n';
    for (int i=0;i<n;++i) {
        int x=mode==0?0:mode==1?rnd.next(-11,11):mode==2?-i:i%3;
        cout<<x<<(i+1==n?'\n':' ');
    }
    for (int i=0;i<q;++i) {
        int l=i%3?rnd.next(1,n):1;
        int r=i%3?rnd.next(l,n):n;
        cout<<l<<' '<<r<<'\n';
    }
}
