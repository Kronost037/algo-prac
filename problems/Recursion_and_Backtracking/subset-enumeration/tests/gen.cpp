#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    vector<int> a(n);
    for (int i=0;i<n;++i) a[i]=mode==2?-1000000+i:i-3;
    shuffle(a.begin(),a.end());
    cout<<n<<'\n';
    for (int x:a) cout<<x<<' ';
    cout<<'\n';
}
