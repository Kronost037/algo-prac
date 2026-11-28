#include <bits/stdc++.h>
using namespace std;

void search(const vector<int>& a,int start,int left,vector<int>& path,vector<vector<int>>& output) {
    if (left==0) { output.push_back(path); return; }
    for (int i=start;i<int(a.size()) && a[i]<=left;++i) {
        path.push_back(a[i]);
        search(a,i,left-a[i],path,output);
        path.pop_back();
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,target; cin>>n>>target;
    vector<int>a(n),path;
    for (int& x:a) cin>>x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    vector<vector<int>>output;
    search(a,0,target,path,output);
    cout<<output.size()<<'\n';
    for (const auto& row:output) {
        cout<<row.size();
        for (int x:row) cout<<' '<<x;
        cout<<'\n';
    }
}
