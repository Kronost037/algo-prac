#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin>>s;
    vector<int> stack;
    for (int i=0;i<int(s.size());++i) {
        char c=s[i];
        if (c=='('||c=='['||c=='{') stack.push_back(i);
        else {
            char open=c==')'?'(':c==']'?'[':'{';
            if (stack.empty()||s[stack.back()]!=open) { cout<<i+1<<'\n'; return 0; }
            stack.pop_back();
        }
    }
    cout<<(stack.empty()?0:stack.front()+1)<<'\n';
}
