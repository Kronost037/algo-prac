#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; long long capacity; cin>>n>>capacity;
    vector<pair<long long,int>>items(n);
    int sum=0;
    for(auto& [w,v]:items) { cin>>w>>v; sum+=v; }
    const long long inf=LLONG_MAX/4;
    vector<long long>cost(sum+1,inf);
    cost[0]=0;
    int top=0;
    for(auto [w,v]:items) {
        top+=v;
        for(int x=top;x>=v;--x) cost[x]=min(cost[x],cost[x-v]+w);
    }
    while(cost[sum]>capacity) --sum;
    cout<<sum<<'\n';
}
