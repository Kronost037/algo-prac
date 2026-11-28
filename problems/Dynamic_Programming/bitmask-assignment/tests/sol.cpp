#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin>>n;
    vector<vector<int>>cost(n,vector<int>(n));
    for(auto& row:cost) for(auto& x:row) cin>>x;
    unsigned full=(1u<<n)-1;
    vector<long long>best(full+1,LLONG_MAX/2);
    best[0]=0;
    for(unsigned mask=0;mask<full;++mask) {
        int i=popcount(mask);
        for(unsigned free=full^mask;free;) {
            unsigned bit=free&-free;
            free^=bit;
            int j=countr_zero(bit);
            best[mask|bit]=min(best[mask|bit],best[mask]+cost[i][j]);
        }
    }
    cout<<best[full]<<'\n';
}
