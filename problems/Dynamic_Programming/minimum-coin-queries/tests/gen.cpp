#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    vector<int> coins(n);
    for (int i=0;i<n;++i) coins[i]=mode==3?2*(i+1):i+1;
    shuffle(coins.begin(),coins.end());

    int q=mode<=1?40:200000;
    cout<<n<<' '<<q<<'\n';
    for(int x:coins) cout<<x<<' ';
    cout<<'\n';
    for(int i=0;i<q;++i) cout<<(i%7==0?0:rnd.next(1,mode<=1?40:100000))<<'\n';
}
