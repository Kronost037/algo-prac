#include <bits/stdc++.h>
using namespace std;

int main() {
    string a,b; cin>>a>>b;
    if(a.size()<b.size()) swap(a,b);
    vector<int>prev(b.size()+1),cur(b.size()+1);
    for(char c:a) {
        for(int j=1;j<=int(b.size());++j)
            cur[j]=c==b[j-1]?prev[j-1]+1:max(prev[j],cur[j-1]);
        swap(prev,cur);
    }
    cout<<prev.back()<<'\n';
}
