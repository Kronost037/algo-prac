#include <bits/stdc++.h>
using namespace std;

struct Node { int value,l,r; };
vector<Node> readTree() {
    int n;cin>>n;
    vector<Node>a(n+1);
    for(int i=1;i<=n;++i)cin>>a[i].value>>a[i].l>>a[i].r;
    return a;
}

vector<int> rootFirst(const vector<Node>& a) {
    vector<int> order{1};
    for(size_t i=0;i<order.size();++i){
        int v=order[i];
        if(a[v].l)order.push_back(a[v].l);
        if(a[v].r)order.push_back(a[v].r);
    }
    return order;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    auto a=readTree();
    auto order=rootFirst(a);
    vector<int> height(a.size(),-1);
    int diameter=0;bool balanced=true;
    for(auto it=order.rbegin();it!=order.rend();++it){
        int v=*it,l=height[a[v].l],r=height[a[v].r];
        height[v]=max(l,r)+1;
        diameter=max(diameter,l+r+2);
        balanced=balanced && abs(l-r)<=1;
    }
    cout<<height[1]<<' '<<diameter<<' '<<(balanced?"YES":"NO")<<'\n';
}
