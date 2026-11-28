#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>a(n);
    for (auto& x:a) cin>>x;
    array<vector<int>,4> answers;
    for (int type=0;type<4;++type) {
        auto index=[&](int i) { return type<2?i%n:n-1-i%n; };
        answers[type].resize(n);
        vector<int> stack;
        for (int i=2*n-1;i>=0;--i) {
            int x=a[index(i)];
            while (!stack.empty()) {
                int y=a[index(stack.back())];
                if (type%2==0?y>x:y<x) break;
                stack.pop_back();
            }
            if (i<n && !stack.empty() && stack.back()-i<n)
                answers[type][index(i)]=stack.back()-i;
            stack.push_back(i);
        }
    }
    while (q--) {
        int t,i; cin>>t>>i;
        cout<<answers[t-1][i-1]<<'\n';
    }
}
