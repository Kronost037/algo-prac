#include <bits/stdc++.h>
using namespace std;

long long pairs(const vector<int>& a,int l,long long target) {
    long long answer=0;
    int r=int(a.size())-1;
    while (l<r) {
        long long sum=(long long)a[l]+a[r];
        if (sum<target) ++l;
        else if (sum>target) --r;
        else if (a[l]==a[r]) {
            long long count=r-l+1;
            return answer+count*(count-1)/2;
        } else {
            int left=a[l],right=a[r],lc=0,rc=0;
            while (l<=r && a[l]==left) { ++l; ++lc; }
            while (r>=l && a[r]==right) { --r; ++rc; }
            answer+=(long long)lc*rc;
        }
    }
    return answer;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long k; cin>>n>>k;
    vector<int>a(n);
    for (int& x:a) cin>>x;
    sort(a.begin(),a.end());
    long long answer=0;
    answer=pairs(a,0,k);
    cout<<answer<<'\n';
}
