#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    vector<int> coins(n);
    for (int i=0;i<n;++i) coins[i]=mode==3?2*(i+1):i+1;
    shuffle(coins.begin(),coins.end());

    int target=mode==0?0:mode==1?rnd.next(1,20):mode==2?100000:99999;
    cout<<n<<' '<<target<<'\n';
    for(int x:coins) cout<<x<<' ';
    cout<<'\n';
}
