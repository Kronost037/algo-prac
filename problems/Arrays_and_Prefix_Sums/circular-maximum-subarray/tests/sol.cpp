#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    long long top=LLONG_MIN,bottom=LLONG_MAX,total=0,hi=0,lo=0;
    while (n--) {
        long long x; cin>>x;
        total+=x;
        hi=max(x,hi+x); lo=min(x,lo+x);
        top=max(top,hi); bottom=min(bottom,lo);
    }
    cout<<(top<0?top:max(top,total-bottom))<<'\n';
}
