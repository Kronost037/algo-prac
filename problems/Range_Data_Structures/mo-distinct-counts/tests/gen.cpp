#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?91:n;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i)cout<<(mode==0?-3:mode==2?i:mode==3?i%17:rnd.next(-30,30))<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i){int l=rnd.next(1,n);cout<<l<<' '<<rnd.next(l,n)<<'\n';}
}
