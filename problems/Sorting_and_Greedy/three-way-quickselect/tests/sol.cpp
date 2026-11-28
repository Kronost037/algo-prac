#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k; --k;
    vector<int>a(n);
    for (int& x:a) cin>>x;
    mt19937 random(random_device{}());
    int lo=0,hi=n;
    while (lo<hi) {
        int pivot=a[uniform_int_distribution<int>(lo,hi-1)(random)];
        int less=lo,i=lo,greater=hi;
        while (i<greater) {
            if (a[i]<pivot) swap(a[less++],a[i++]);
            else if (a[i]>pivot) swap(a[i],a[--greater]);
            else ++i;
        }
        if (k<less) hi=less;
        else if (k>=greater) lo=greater;
        else { cout<<pivot<<'\n'; return 0; }
    }
}
