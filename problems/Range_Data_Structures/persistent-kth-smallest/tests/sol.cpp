#include <bits/stdc++.h>
using namespace std;

struct Node { int left=0,right=0,count=0; };
class PrefixTrees {
    vector<Node> nodes{Node{}};
    int width;
    int insert(int old,int l,int r,int rank) {
        int next=nodes.size();
        nodes.push_back(nodes[old]);
        ++nodes[next].count;
        if(l<r) {
            int mid=(l+r)/2;
            if(rank<=mid) nodes[next].left=insert(nodes[old].left,l,mid,rank);
            else nodes[next].right=insert(nodes[old].right,mid+1,r,rank);
        }
        return next;
    }
public:
    PrefixTrees(int width,int n):width(width) { nodes.reserve(1+size_t(n)*(1+bit_width(unsigned(width-1)))); }
    int insert(int old,int rank) { return insert(old,0,width-1,rank); }
    int kth(int before,int after,int k) const {
        int l=0,r=width-1;
        while(l<r) {
            int mid=(l+r)/2;
            int left=nodes[after].left,right=nodes[before].left;
            int count=nodes[left].count-nodes[right].count;
            if(k<=count) { after=left; before=right; r=mid; }
            else { k-=count; after=nodes[after].right; before=nodes[before].right; l=mid+1; }
        }
        return l;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int>a(n);
    for(int& x:a) cin>>x;
    auto keys=a;
    sort(keys.begin(),keys.end());
    keys.erase(unique(keys.begin(),keys.end()),keys.end());
    PrefixTrees trees(keys.size(),n);
    vector<int>root(n+1);
    for(int i=0;i<n;++i)
        root[i+1]=trees.insert(root[i],lower_bound(keys.begin(),keys.end(),a[i])-keys.begin());
    while(q--) {
        int l,r,k; cin>>l>>r>>k;
        cout<<keys[trees.kth(root[l-1],root[r],k)]<<'\n';
    }
}
