#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?71:200000;
    vector<long long> f(n);
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) {
        f[i]=mode==2?1000000000:mode==3?0:rnd.next(0,8);
        cout<<f[i]<<(i+1==n?'\n':' ');
    }
    for(int i=0;i<q;++i) {
        if(i%3==0) {
            int j=mode>=2?(i%2?0:n-1):rnd.next(0,n-1);
            long long delta=i%2?rnd.next(0,1000000000):-min(f[j],(long long)rnd.next(0,1000000000));
            f[j]+=delta;
            cout<<"ADD "<<j+1<<' '<<delta<<'\n';
        } else {
            long long k=mode>=2?(i%5==0?1000000000000000LL:1LL+i*1000000000):rnd.next(1,30);
            cout<<"KTH "<<k<<'\n';
        }
    }
}
