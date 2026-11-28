#include <bits/stdc++.h>
using namespace std;

struct Function { long long a,b; };

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q;
    long long mod;
    cin>>n>>q>>mod;
    auto join=[mod](Function left,Function right) {
        return Function{right.a*left.a%mod,(right.a*left.b+right.b)%mod};
    };
    Function identity{1%mod,0};
    int size=1;
    while (size<n) size*=2;
    vector<Function>tree(2*size,identity);
    for (int i=0;i<n;++i) cin>>tree[size+i].a>>tree[size+i].b;
    for (int i=size-1;i>=1;--i) tree[i]=join(tree[i*2],tree[i*2+1]);
    while (q--) {
        string op; cin>>op;
        if (op=="SET") {
            int i; Function function;
            cin>>i>>function.a>>function.b;
            int node=size+i-1;
            tree[node]=function;
            while ((node/=2)>0) tree[node]=join(tree[2*node],tree[2*node+1]);
        } else {
            int l,r; long long x;
            cin>>l>>r>>x;
            Function left=identity,right=identity;
            for (l+=size-1,r+=size;l<r;l/=2,r/=2) {
                if (l%2) left=join(left,tree[l++]);
                if (r%2) right=join(tree[--r],right);
            }
            auto answer=join(left,right);
            cout<<(answer.a*x+answer.b)%mod<<'\n';
        }
    }
}
