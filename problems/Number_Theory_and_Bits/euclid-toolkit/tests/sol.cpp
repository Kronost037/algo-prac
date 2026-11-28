#include <bits/stdc++.h>
using namespace std;

pair<long long,long long> coefficients(long long a,long long b){
    if(b==0)return {1,0};
    auto [x,y]=coefficients(b,a%b);
    return {y,x-a/b*y};
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int q;cin>>q;
    while(q--){
        string op;long long a,b;cin>>op>>a>>b;
        long long g=gcd(a,b);
        if(op=="GCD")cout<<g<<'\n';
        else if(op=="LCM")cout<<(g?a/g*b:0)<<'\n';
        else if(g!=1)cout<<"NONE\n";
        else{
            auto [x,y]=coefficients((a%b+b)%b,b);
            cout<<(x%b+b)%b<<'\n';
        }
    }
}
