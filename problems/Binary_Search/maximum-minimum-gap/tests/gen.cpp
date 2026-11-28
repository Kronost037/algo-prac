#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int k=mode==0?2:mode==1?rnd.next(2,n):mode==2?n:2;
    int step=2000000000/(n-1);
    vector<int>a(n);
    for (int i=0;i<n;++i) a[i]=int(-1000000000LL+1LL*i*step);
    if (mode==1) for (int i=1;i+1<n;++i) a[i]+=rnd.next(0,step-1);
    shuffle(a.begin(),a.end());
    cout<<n<<' '<<k<<'\n';
    for (int i=0;i<n;++i) cout<<a[i]<<(i+1==n?'\n':' ');
}
