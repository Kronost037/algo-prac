#include <bits/stdc++.h>
using namespace std;

long long best(const vector<int>& a,int l,int r) {
    long long two=0,one=0;
    for (int i=l;i<r;++i) {
        long long next=max(one,two+a[i]);
        two=one;
        one=next;
    }
    return one;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<int>a(n);
    for (int& x:a) cin>>x;
    long long line=best(a,0,n);
    cout<<line<<' '<<(n==1?line:max(best(a,1,n),best(a,0,n-1)))<<'\n';
}
