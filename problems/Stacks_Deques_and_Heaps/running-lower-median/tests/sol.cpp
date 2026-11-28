#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    priority_queue<int> low;
    priority_queue<int,vector<int>,greater<int>> high;
    while (n--) {
        int x; cin>>x;
        if (low.empty() || x<=low.top()) low.push(x);
        else high.push(x);
        if (low.size()>high.size()+1) { high.push(low.top()); low.pop(); }
        if (high.size()>low.size()) { low.push(high.top()); high.pop(); }
        cout<<low.top()<<'\n';
    }
}
