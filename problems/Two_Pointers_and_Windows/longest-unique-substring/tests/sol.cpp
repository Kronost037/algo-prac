#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin>>s;
    array<int,26> last;
    last.fill(-1);
    int left=0,best=0;
    for (int r=0;r<int(s.size());++r) {
        int c=s[r]-'a';
        left=max(left,last[c]+1);
        last[c]=r;
        best=max(best,r-left+1);
    }
    cout<<best<<'\n';
}
