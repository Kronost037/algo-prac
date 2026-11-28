#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    deque<pair<int,int>> low,high;
    for (int i=0;i<n;++i) {
        int x; cin>>x;
        if (!low.empty() && low.front().first<=i-k) low.pop_front();
        if (!high.empty() && high.front().first<=i-k) high.pop_front();
        while (!low.empty() && low.back().second>=x) low.pop_back();
        while (!high.empty() && high.back().second<=x) high.pop_back();
        low.emplace_back(i,x);
        high.emplace_back(i,x);
        if (i>=k-1) cout<<low.front().second<<' '<<high.front().second<<'\n';
    }
}
