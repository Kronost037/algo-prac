#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?101:100000;
    cout<<n<<' '<<q<<'\n';
    for(int i=1;i<=n;++i)cout<<rnd.next(-10,10)<<(i==n?'\n':' ');
    for(int i=2;i<=n;++i)cout<<(mode==2?i-1:mode==3?1:rnd.next(1,i-1))<<' '<<i<<'\n';

    for(int i=0;i<q;++i){
        int v=mode>=2 && i%3==0?1:rnd.next(1,n);
        if(i%2==0)cout<<"ADD "<<v<<' '<<rnd.next(-1000000,1000000)<<'\n';
        else cout<<"SUM "<<v<<'\n';
    }
}
