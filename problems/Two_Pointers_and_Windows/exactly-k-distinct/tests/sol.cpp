#include <bits/stdc++.h>
using namespace std;

long long atMost(const vector<int>& a,int k) {
    vector<int> freq(a.size());
    int l=0,distinct=0;
    long long count=0;
    for (int r=0;r<int(a.size());++r) {
        distinct+=++freq[a[r]]==1;
        while (distinct>k) distinct-=--freq[a[l++]]==0;
        count+=r-l+1;
    }
    return count;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<int>a(n);
    for (auto& x:a) cin>>x;
    auto keys=a;
    sort(keys.begin(),keys.end());
    keys.erase(unique(keys.begin(),keys.end()),keys.end());
    for (auto& x:a) x=lower_bound(keys.begin(),keys.end(),x)-keys.begin();
    cout<<atMost(a,k)-atMost(a,k-1)<<'\n';
}
