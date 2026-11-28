#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    vector<long long>a;
    a.push_back(mode==2?LLONG_MIN:0);
    a.push_back(mode==2?0:mode==3?LLONG_MAX:-7);
    for(int i=0;i<(n-2)/2;++i){a.push_back(i+1);a.push_back(i+1);}
    shuffle(a.begin(),a.end());
    cout<<n<<'\n';
    for(int i=0;i<n;++i)cout<<a[i]<<(i+1==n?'\n':' ');
}
