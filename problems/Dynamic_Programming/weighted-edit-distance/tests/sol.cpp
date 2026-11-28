#include <bits/stdc++.h>
using namespace std;

int main() {
    string a,b;
    long long ins,del,rep;
    cin>>a>>b>>ins>>del>>rep;
    vector<long long>prev(b.size()+1),cur(b.size()+1);
    for(int j=1;j<=int(b.size());++j) prev[j]=j*ins;
    for(int i=1;i<=int(a.size());++i) {
        cur[0]=i*del;
        for(int j=1;j<=int(b.size());++j)
            cur[j]=min({prev[j]+del,cur[j-1]+ins,prev[j-1]+(a[i-1]==b[j-1]?0:rep)});
        swap(prev,cur);
    }
    cout<<prev.back()<<'\n';
}
