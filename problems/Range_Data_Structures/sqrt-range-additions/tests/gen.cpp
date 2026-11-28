#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?80:100000;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?1000000000:rnd.next(-10,10))<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i) {
        int j=rnd.next(1,n);
        if(i%4==0) cout<<"GET "<<j<<'\n';
        else if(mode==2) cout<<"ADD 1 "<<n<<" 1000000000\n";
        else cout<<"ADD "<<j<<' '<<rnd.next(j,n)<<' '<<rnd.next(-100,100)<<'\n';
    }
}
