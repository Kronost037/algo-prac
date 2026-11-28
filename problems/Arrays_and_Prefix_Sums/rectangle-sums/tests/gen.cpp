#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=opt<int>(3), q=mode<=1 ? 30 : 200000;
    cout<<n<<' '<<m<<' '<<q<<'\n';
    for (int r=0;r<n;++r) for (int c=0;c<m;++c) {
        int x=mode==2 ? 1000000000 : mode==3 ? ((r+c)%2 ? -1000000000 : 1000000000) : rnd.next(-9,9);
        cout<<x<<(c+1==m?'\n':' ');
    }
    for (int i=0;i<q;++i) {
        int a=1,b=1,c=n,d=m;
        if (i%3!=0) { a=rnd.next(1,n); b=rnd.next(1,m); c=rnd.next(a,n); d=rnd.next(b,m); }
        cout<<a<<' '<<b<<' '<<c<<' '<<d<<'\n';
    }
}
