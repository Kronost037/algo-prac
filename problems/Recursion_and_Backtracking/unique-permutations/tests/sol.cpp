#include <bits/stdc++.h>
using namespace std;

void generate(const vector<int>& keys,vector<int>& count,vector<int>& path,int n) {
    if (int(path.size())==n) {
        for (int i=0;i<n;++i) cout<<path[i]<<(i+1==n?'\n':' ');
        return;
    }
    for (int i=0;i<int(keys.size());++i) if (count[i]) {
        --count[i];
        path.push_back(keys[i]);
        generate(keys,count,path,n);
        path.pop_back();
        ++count[i];
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    map<int,int> frequency;
    for (int i=0;i<n;++i) { int x; cin>>x; ++frequency[x]; }
    vector<int> keys,count,path;
    for (auto [x,c]:frequency) { keys.push_back(x); count.push_back(c); }
    generate(keys,count,path,n);
}
