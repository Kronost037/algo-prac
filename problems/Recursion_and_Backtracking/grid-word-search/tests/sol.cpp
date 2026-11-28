#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m; cin>>n>>m;
    vector<string>a(n);
    for (auto& s:a) cin>>s;
    string word; cin>>word;
    const int dr[]={1,-1,0,0},dc[]={0,0,1,-1};
    auto search=[&](auto&& self,int r,int c,int k) -> bool {
        if (r<0 || r>=n || c<0 || c>=m || a[r][c]!=word[k]) return false;
        if (k+1==int(word.size())) return true;
        char before=a[r][c];
        a[r][c]='.';
        bool found=false;
        for (int d=0;d<4 && !found;++d) found=self(self,r+dr[d],c+dc[d],k+1);
        a[r][c]=before;
        return found;
    };
    for(int r=0;r<n;++r) for(int c=0;c<m;++c) if(search(search,r,c,0)) {
        cout<<"YES\n";
        return 0;
    }
    cout<<"NO\n";
}
