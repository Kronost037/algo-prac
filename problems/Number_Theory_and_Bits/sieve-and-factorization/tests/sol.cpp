#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;cin>>q;vector<pair<string,int>>queries(q);
    int limit=1;
    for(auto& [op,x]:queries){cin>>op>>x;limit=max(limit,x);}
    vector<int>spf(limit+1);
    for(int p=2;p<=limit;++p)if(!spf[p]){
        spf[p]=p;
        if(p<=limit/p)for(int m=p*p;m<=limit;m+=p)if(!spf[m])spf[m]=p;
    }
    for(auto [op,x]:queries){
        vector<pair<int,int>>factors;
        int divisors=1;
        while(x>1){
            int p=spf[x],count=0;
            do{x/=p;++count;}while(x>1 && spf[x]==p);
            factors.emplace_back(p,count);divisors*=count+1;
        }
        if(op=="DIV")cout<<divisors;
        else{
            cout<<factors.size();
            for(auto [p,k]:factors)cout<<' '<<p<<' '<<k;
        }
        cout<<'\n';
    }
}
