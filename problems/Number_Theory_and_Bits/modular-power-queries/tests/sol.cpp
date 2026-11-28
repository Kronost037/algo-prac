#include <bits/stdc++.h>
using namespace std;

using U64=uint64_t;
using U128=__uint128_t;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;cin>>q;
    while(q--){
        U64 a,b,m;cin>>a>>b>>m;
        a%=m;
        U64 answer=1%m;
        for(;b;b>>=1){
            if(b&1)answer=U128(answer)*a%m;
            a=U128(a)*a%m;
        }
        cout<<answer<<'\n';
    }
}
