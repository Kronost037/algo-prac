#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;cin>>n;
    vector<int64_t>a(n);
    uint64_t both=0;
    for(auto& x:a){cin>>x;both^=uint64_t(x);}
    uint64_t bit=both&-both,l=0,r=0;
    for(int64_t x:a)(uint64_t(x)&bit?l:r)^=uint64_t(x);
    int64_t x=bit_cast<int64_t>(l),y=bit_cast<int64_t>(r);
    cout<<min(x,y)<<' '<<max(x,y)<<'\n';
}
