#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin>>n;
    vector<pair<int,int>> events;
    while (n--) {
        int l,r; cin>>l>>r;
        events.emplace_back(l,1);
        events.emplace_back(r,-1);
    }
    sort(events.begin(),events.end());
    int peak=0,active=0,last=events.front().first;
    long long covered=0;
    for (int i=0;i<int(events.size());) {
        int x=events[i].first;
        if (active) covered+=(long long)x-last;
        do { active+=events[i++].second; }
        while (i<int(events.size()) && events[i].first==x);
        peak=max(peak,active);
        last=x;
    }
    cout<<peak<<' '<<covered<<'\n';
}
