#include <bits/stdc++.h>
using namespace std;

class Fenwick {
    vector<long long> tree;
public:
    explicit Fenwick(int n):tree(n+1){}
    void add(int i,long long x) {
        for (;i<int(tree.size());i+=i&-i) tree[i]+=x;
    }
    long long prefix(int i) const {
        long long sum=0;
        for (;i>0;i-=i&-i) sum+=tree[i];
        return sum;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n>>q;
    Fenwick tree(n);
    for (int i=1;i<=n;++i) {
        long long x; cin>>x;
        tree.add(i,x);
    }
    while (q--) {
        string op; int i; long long x; cin>>op>>i>>x;
        if (op=="ADD") tree.add(i,x);
        else cout<<tree.prefix(x)-tree.prefix(i-1)<<'\n';
    }
}
