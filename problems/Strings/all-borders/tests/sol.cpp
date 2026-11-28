#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; cin>>s;
    int n=s.size();
    vector<int>pi(n),answers;
    for (int i=1;i<n;++i) {
        int j=pi[i-1];
        while (j && s[i]!=s[j]) j=pi[j-1];
        pi[i]=j+(s[i]==s[j]);
    }
    for (int k=pi.back();k;k=pi[k-1]) answers.push_back(k);
    cout<<answers.size()<<'\n';
    reverse(answers.begin(),answers.end());
    for (size_t i=0;i<answers.size();++i) cout<<answers[i]<<(i+1==answers.size()?'\n':' ');
}
