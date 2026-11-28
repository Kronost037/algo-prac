#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long k; cin>>n>>k;
    unordered_map<long long,int> count;
    count.reserve(2*n+1);
    count[0]=1;
    long long prefix=0,answer=0;
    while (n--) {
        long long x; cin>>x;
        prefix+=x;
        auto it=count.find(prefix-k);
        if (it!=count.end()) answer+=it->second;
        ++count[prefix];
    }
    cout<<answer<<'\n';
}
