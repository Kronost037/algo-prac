#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?88:200000;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?i-1000000000:mode==3?7:rnd.next(-30,30))<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i) {
        int l=i%5?rnd.next(1,n):1,r=i%5?rnd.next(l,n):n;
        int k=i%3==0?1:i%3==1?r-l+1:rnd.next(1,r-l+1);
        cout<<l<<' '<<r<<' '<<k<<'\n';
    }
}
