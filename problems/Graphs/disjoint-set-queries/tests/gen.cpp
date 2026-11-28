#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int q=n<100?101:200000;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<q;++i){
        int u=mode==2?i%n+1:rnd.next(1,n),v=mode==2?u%n+1:rnd.next(1,n);
        if(i%4<2)cout<<"UNION "<<u<<' '<<(mode==3?u:v)<<'\n';
        else if(i%4==2)cout<<"SAME "<<u<<' '<<v<<'\n';
        else cout<<"SIZE "<<u<<'\n';
    }
}
