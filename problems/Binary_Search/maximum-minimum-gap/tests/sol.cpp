#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<long long>a(n);
    for (auto& x:a) cin>>x;
    sort(a.begin(),a.end());
    long long lo=0,hi=a.back()-a.front();
    while (lo<hi) {
        long long mid=lo+(hi-lo+1)/2,last=a.front();
        int count=1;
        for (long long x:a) if (x-last>=mid) {
            last=x;
            ++count;
        }
        if (count>=k) lo=mid;
        else hi=mid-1;
    }
    cout<<lo<<'\n';
}
