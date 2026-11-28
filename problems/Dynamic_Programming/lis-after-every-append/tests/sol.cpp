#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<int>tails;
    while(n--) {
        int x; cin>>x;
        auto at=lower_bound(tails.begin(),tails.end(),x);
        if(at==tails.end()) tails.push_back(x);
        else *at=x;
        cout<<tails.size()<<'\n';
    }
}
