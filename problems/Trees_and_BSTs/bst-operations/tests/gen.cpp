#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    for(int i=0;i<n;++i){
        int x=mode==2?i:mode==3?i/5:rnd.next(-15,15);
        if(i%5<2 || mode==2 && i<n/2)cout<<"ADD "<<x<<'\n';
        else if(i%5==2)cout<<"ERASE "<<(mode==3?x-1:x)<<'\n';
        else cout<<(i%5==3?"FLOOR ":"CEIL ")<<x<<'\n';
    }
}
