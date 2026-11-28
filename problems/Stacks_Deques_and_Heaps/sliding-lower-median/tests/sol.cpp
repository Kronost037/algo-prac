#include <bits/stdc++.h>
using namespace std;

class Median {
    multiset<int> low,high;
    void balance() {
        size_t target=(low.size()+high.size()+1)/2;
        while (low.size()>target) {
            auto it=prev(low.end());
            high.insert(*it);
            low.erase(it);
        }
        while (low.size()<target) {
            auto it=high.begin();
            low.insert(*it);
            high.erase(it);
        }
    }
public:
    void add(int x) {
        if (low.empty() || x<=*low.rbegin()) low.insert(x);
        else high.insert(x);
        balance();
    }
    void remove(int x) {
        auto it=low.find(x);
        if (it!=low.end()) low.erase(it);
        else high.erase(high.find(x));
        balance();
    }
    int middle() const { return *low.rbegin(); }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<int>a(n);
    Median median;
    for (int i=0;i<n;++i) {
        cin>>a[i];
        if (i>=k) median.remove(a[i-k]);
        median.add(a[i]);
        if (i>=k-1) cout<<median.middle()<<'\n';
    }
}
