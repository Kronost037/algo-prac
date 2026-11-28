#include <bits/stdc++.h>
using namespace std;

struct Node {int key,left=0,right=0,size=1;uint64_t priority;};
class Treap{
    vector<Node>a{{0,0,0,0,0}};
    mt19937_64 random{random_device{}()};
    int root=0;
    void pull(int v){a[v].size=1+a[a[v].left].size+a[a[v].right].size;}
    pair<int,int> split(int v,int x){
        if(!v)return {0,0};
        if(a[v].key<x){
            auto [l,r]=split(a[v].right,x);a[v].right=l;pull(v);return {v,r};
        }
        auto [l,r]=split(a[v].left,x);a[v].left=r;pull(v);return {l,v};
    }
    int merge(int l,int r){
        if(!l||!r)return l?l:r;
        if(a[l].priority>a[r].priority){a[l].right=merge(a[l].right,r);pull(l);return l;}
        a[r].left=merge(l,a[r].left);pull(r);return r;
    }
public:
    void set(int x,bool present){
        auto [l,tail]=split(root,x);
        auto [same,r]=split(tail,x+1);
        if(present&&!same){same=a.size();a.push_back({x,0,0,1,random()});}
        root=merge(merge(l,present?same:0),r);
    }
    int rank(int x)const{
        int count=0;
        for(int v=root;v;){
            if(x<=a[v].key)v=a[v].left;
            else{count+=a[a[v].left].size+1;v=a[v].right;}
        }
        return count;
    }
    optional<int> kth(int k)const{
        for(int v=root;v;){
            int here=a[a[v].left].size+1;
            if(k==here)return a[v].key;
            if(k<here)v=a[v].left;
            else{k-=here;v=a[v].right;}
        }
        return nullopt;
    }
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;cin>>q;Treap t;
    while(q--){
        string op;int x;cin>>op>>x;
        if(op=="RANK")cout<<t.rank(x)<<'\n';
        else if(op=="KTH"){auto v=t.kth(x);if(v)cout<<*v<<'\n';else cout<<"NONE\n";}
        else t.set(x,op=="ADD");
    }
}
