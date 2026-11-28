#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int>& a,vector<int>& buffer,int l,int r) {
    if (r-l<2) return 0;
    int m=l+(r-l)/2;
    long long answer=solve(a,buffer,l,m);
    answer+=solve(a,buffer,m,r);
    int i=l,j=m;
    for (int k=l;k<r;++k) {
        if (j==r || (i<m && a[i]<=a[j])) buffer[k]=a[i++];
        else {
            buffer[k]=a[j++];
            answer+=m-i;
        }
    }
    copy(buffer.begin()+l,buffer.begin()+r,a.begin()+l);
    return answer;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<int>a(n),buffer(n);
    for (int& x:a) cin>>x;
    cout<<solve(a,buffer,0,n)<<'\n';
}
