#include <bits/stdc++.h>
using namespace std;

class MaxTree {
    int size;
    vector<int> tree;
    int first(int node,int l,int r,int ql,int qr,int x) const {
        if(r<ql || l>qr || tree[node]<=x) return 0;
        if(l==r) return l;
        int mid=(l+r)/2;
        int left=first(node*2,l,mid,ql,qr,x);
        return left?left:first(node*2+1,mid+1,r,ql,qr,x);
    }
public:
    explicit MaxTree(const vector<int>& a):size(bit_ceil(unsigned(a.size()))),tree(size*2,INT_MIN) {
        copy(a.begin(),a.end(),tree.begin()+size);
        for(int i=size-1;i;--i) tree[i]=max(tree[2*i],tree[2*i+1]);
    }
    void set(int i,int x) {
        int p=size+i-1;
        tree[p]=x;
        while((p/=2)>0) tree[p]=max(tree[2*p],tree[2*p+1]);
    }
    int first(int l,int r,int x) const { return first(1,1,size,l,r,x); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>a(n);
    for(int& x:a) cin>>x;
    MaxTree t(a);
    while(q--) {
        string op; int l,r,x; cin>>op>>l>>r;
        if(op=="SET") t.set(l,r);
        else { cin>>x; cout<<t.first(l,r,x)<<'\n'; }
    }
}
