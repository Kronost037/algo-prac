#include <bits/stdc++.h>
using namespace std;

struct Node { int value,l,r; };
vector<Node> readTree() {
    int n;cin>>n;
    vector<Node>a(n+1);
    for(int i=1;i<=n;++i)cin>>a[i].value>>a[i].l>>a[i].r;
    return a;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    auto a=readTree();
    vector<tuple<int,long long,long long>> st{{1,LLONG_MIN,LLONG_MAX}};
    while(!st.empty()){
        auto [v,low,high]=st.back();st.pop_back();
        if(a[v].value<=low||a[v].value>=high){cout<<"NO\n";return 0;}
        if(a[v].l)st.emplace_back(a[v].l,low,a[v].value);
        if(a[v].r)st.emplace_back(a[v].r,a[v].value,high);
    }
    cout<<"YES\n";
}
