#include <bits/stdc++.h>
using namespace std;

struct Query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<int>a(n);
    for(auto& x:a)cin>>x;
    auto keys=a;
    sort(keys.begin(),keys.end());keys.erase(unique(keys.begin(),keys.end()),keys.end());
    for(auto& x:a)x=lower_bound(keys.begin(),keys.end(),x)-keys.begin();
    int block=max(1,int(n/sqrt(q)));
    vector<Query>queries(q);
    for(int i=0;i<q;++i){auto& v=queries[i];cin>>v.l>>v.r;--v.l;--v.r;v.id=i;}
    sort(queries.begin(),queries.end(),[&](Query a,Query b){
        int i=a.l/block,j=b.l/block;
        return i!=j?i<j:i%2?a.r>b.r:a.r<b.r;
    });
    vector<int> freq(keys.size()),answer(q);
    int l=0,r=-1,count=0;
    auto add=[&](int i){count+=++freq[a[i]]==1;};
    auto remove=[&](int i){count-=--freq[a[i]]==0;};
    for(auto v:queries){
        while(l>v.l)add(--l);
        while(r<v.r)add(++r);
        while(l<v.l)remove(l++);
        while(r>v.r)remove(r--);
        answer[v.id]=count;
    }
    for(int x:answer)cout<<x<<'\n';
}
