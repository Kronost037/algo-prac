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
    auto a=readTree();auto order=rootFirst(a);
    vector<long long> down(a.size());
    long long answer=LLONG_MIN;
    for(auto it=order.rbegin();it!=order.rend();++it){
        int v=*it;
        long long l=max(0LL,down[a[v].l]),r=max(0LL,down[a[v].r]);
        answer=max(answer,a[v].value+l+r);
        down[v]=a[v].value+max(l,r);
    }
    cout<<answer<<'\n';
}
