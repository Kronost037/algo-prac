#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int target=mode==0?0:mode==1?rnd.next(1,20):35;
    cout<<n<<' '<<target<<'\n';
    for(int i=0;i<n;++i) cout<<(mode==2?i+1:mode==3?2:rnd.next(1,50))<<(i+1==n?'\n':' ');
}
