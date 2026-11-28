#include <bits/stdc++.h>
using namespace std;

long long countWays(const vector<unsigned>& allowed,unsigned full,int row,unsigned cols,unsigned left,unsigned right) {
    if (row==int(allowed.size())) return 1;
    unsigned free=allowed[row]&~(cols|left|right);
    long long total=0;
    while (free) {
        unsigned bit=free&-free;
        free^=bit;
        total+=countWays(allowed,full,row+1,cols|bit,((left|bit)<<1)&full,(right|bit)>>1);
    }
    return total;
}
int main() {
    int n; cin>>n;
    unsigned full=(1u<<n)-1;
    vector<unsigned>allowed(n,full);
    for(int r=0;r<n;++r) {
        string s; cin>>s;
        size_t col=s.find('Q');
        if(col!=string::npos) allowed[r]=1u<<col;
    }
    cout<<countWays(allowed,full,0,0,0,0)<<'\n';
}
