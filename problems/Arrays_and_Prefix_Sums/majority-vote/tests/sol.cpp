#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<int>a(n);
    int candidate=0,balance=0;
    for (int& x:a) {
        cin>>x;
        if (!balance) candidate=x;
        balance+=x==candidate?1:-1;
    }
    if (count(a.begin(),a.end(),candidate)>n/2) cout<<candidate<<'\n';
    else cout<<"NONE\n";
}
