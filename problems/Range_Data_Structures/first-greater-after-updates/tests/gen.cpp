#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?90:200000;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?0:mode==3?-i:rnd.next(-10,10))<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i) {
        int j=rnd.next(1,n);
        if(i%5==0) cout<<"SET "<<(mode==2?n:j)<<' '<<(mode==2?i%2:rnd.next(-10,10))<<'\n';
        else if(mode==2) cout<<"FIRST 1 "<<n<<" 0\n";
        else cout<<"FIRST "<<j<<' '<<rnd.next(j,n)<<' '<<rnd.next(-10,10)<<'\n';
    }
}
