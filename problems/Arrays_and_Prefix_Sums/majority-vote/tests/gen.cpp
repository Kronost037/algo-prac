#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    vector<int>a(n);
    for (int i=0;i<n;++i) a[i]=mode==0?-9:mode==1?rnd.next(-4,4):mode==2?i%2:i<=n/2?-1000000000:i;
    shuffle(a.begin(),a.end());
    for (int i=0;i<n;++i) cout<<a[i]<<(i+1==n?'\n':' ');
}
