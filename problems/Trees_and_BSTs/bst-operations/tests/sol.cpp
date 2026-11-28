#include <bits/stdc++.h>
using namespace std;

struct Node {int key,left=0,right=0;};
class BST {
    vector<Node>a{{0}};
    int insert(int v,int x){
        if(!v){a.push_back({x});return int(a.size())-1;}
        if(x<a[v].key)a[v].left=insert(a[v].left,x);
        if(x>a[v].key)a[v].right=insert(a[v].right,x);
        return v;
    }
    int erase(int v,int x){
        if(!v)return 0;
        if(x<a[v].key)a[v].left=erase(a[v].left,x);
        else if(x>a[v].key)a[v].right=erase(a[v].right,x);
        else{
            if(!a[v].left)return a[v].right;
            if(!a[v].right)return a[v].left;
            int s=a[v].right;
            while(a[s].left)s=a[s].left;
            a[v].key=a[s].key;
            a[v].right=erase(a[v].right,a[s].key);
        }
        return v;
    }
    int root=0;
public:
    void add(int x){root=insert(root,x);}
    void remove(int x){root=erase(root,x);}
    optional<int> bound(int x,bool floor) const{
        optional<int> best;
        for(int v=root;v;){
            int key=a[v].key;
            if(key==x)return x;
            if(floor?key<x:key>x)best=key;
            v=key<x?a[v].right:a[v].left;
        }
        return best;
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;cin>>q;BST tree;
    while(q--){
        string op;int x;cin>>op>>x;
        if(op=="ADD")tree.add(x);
        else if(op=="ERASE")tree.remove(x);
        else{
            auto ans=tree.bound(x,op=="FLOOR");
            if(ans)cout<<*ans<<'\n';else cout<<"NONE\n";
        }
    }
}
