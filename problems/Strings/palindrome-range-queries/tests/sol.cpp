#include <bits/stdc++.h>
using namespace std;

vector<int> radii(const string& s,bool even) {
    int n=s.size(),l=0,r=-1;
    vector<int>d(n);
    for (int i=0;i<n;++i) {
        int k=i>r?(even?0:1):min(d[l+r-i+even],r-i+1);
        while (i-k-(even?1:0)>=0 && i+k<n && s[i-k-(even?1:0)]==s[i+k]) ++k;
        d[i]=k;
        if (i+k-1>r) {
            l=i-k+(even?0:1);
            r=i+k-1;
        }
    }
    return d;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; int q; cin>>s>>q;
    auto odd=radii(s,false),even=radii(s,true);
    while (q--) {
        int l,r; cin>>l>>r; --l; --r;
        int length=r-l+1,center=l+length/2;
        bool yes=length%2?odd[center]>=length/2+1:even[center]>=length/2;
        cout<<(yes?"YES\n":"NO\n");
    }
}
