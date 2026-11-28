#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string p; int count; cin>>p>>count;
    int m=p.size();
    vector<int>pi(m),matches;
    for (int i=1;i<m;++i) {
        int j=pi[i-1];
        while (j && p[i]!=p[j]) j=pi[j-1];
        pi[i]=j+(p[i]==p[j]);
    }
    int j=0,position=0;
    while (count--) {
        string chunk; cin>>chunk;
        for (char c:chunk) {
            ++position;
            while (j && c!=p[j]) j=pi[j-1];
            if (c==p[j]) ++j;
            if (j==m) {
                matches.push_back(position-m+1);
                j=pi[j-1];
            }
        }
    }
    cout<<matches.size()<<'\n';
    for (size_t i=0;i<matches.size();++i) cout<<matches[i]<<(i+1==matches.size()?'\n':' ');
}
