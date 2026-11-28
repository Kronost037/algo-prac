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
    array<vector<int>,4> out;
    vector<pair<int,int>> st{{1,0}};
    while(!st.empty()){
        auto [v,stage]=st.back();st.pop_back();
        out[stage].push_back(v);
        if(stage<2){
            st.emplace_back(v,stage+1);
            int child=stage==0?a[v].l:a[v].r;
            if(child)st.emplace_back(child,0);
        }
    }
    auto& order=out[3];order.push_back(1);
    for(size_t i=0;i<order.size();++i){
        int v=order[i];
        if(a[v].l)order.push_back(a[v].l);
        if(a[v].r)order.push_back(a[v].r);
    }
    for(const auto& row:out){
        for(size_t i=0;i<row.size();++i)cout<<row[i]<<(i+1==row.size()?'\n':' ');
    }
}
