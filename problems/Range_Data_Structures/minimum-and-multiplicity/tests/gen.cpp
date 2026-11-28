#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?90:200000;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?0:mode==3?i%7:rnd.next(-10,10))<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i) {
        int j=rnd.next(1,n);
        if(i%3==0) cout<<"SET "<<j<<' '<<(mode>=2?i%2:rnd.next(-10,10))<<'\n';
        else cout<<"MIN "<<(mode==2?1:j)<<' '<<(mode==2?n:rnd.next(j,n))<<'\n';
    }
}
