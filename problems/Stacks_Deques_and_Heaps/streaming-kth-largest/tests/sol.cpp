#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    priority_queue<int,vector<int>,greater<int>> top;
    for (int i=1;i<=n;++i) {
        int x; cin>>x;
        top.push(x);
        if (int(top.size())>k) top.pop();
        if (i>=k) cout<<top.top()<<'\n';
    }
}
