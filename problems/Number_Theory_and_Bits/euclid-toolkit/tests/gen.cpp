#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i){
        int a=mode==2?1000000000:mode==3?0:rnd.next(0,1000000000);
        int b=mode==2?999999999:mode==3?2:rnd.next(2,1000000000);
        if(i%3==0)cout<<"GCD "<<a<<' '<<b<<'\n';
        else if(i%3==1)cout<<"LCM "<<a<<' '<<b<<'\n';
        else cout<<"INV "<<-a<<' '<<b<<'\n';
    }
}
