#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<long long>a(n);
    for (auto& x:a) cin>>x;
    long long lo=*max_element(a.begin(),a.end()),hi=accumulate(a.begin(),a.end(),0LL);
    while (lo<hi) {
        long long mid=lo+(hi-lo)/2,sum=0;
        int parts=1;
        for (long long x:a) {
            if (sum+x>mid) { ++parts; sum=0; }
            sum+=x;
        }
        if (parts<=k) hi=mid;
        else lo=mid+1;
    }
    cout<<lo<<'\n';
}
