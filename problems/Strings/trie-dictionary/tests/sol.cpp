#include <bits/stdc++.h>
using namespace std;

struct Node {
    array<int,26> next{};
    int terminal=0,subtree=0;
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin>>q;
    vector<Node> trie(1);
    while (q--) {
        string op,w; cin>>op>>w;
        vector<int> path;
        int v=0;
        for (char c:w) {
            int id=c-'a', child=trie[v].next[id];
            if (!child && op=="ADD") {
                child=trie.size();
                trie[v].next[id]=child;
                trie.emplace_back();
            }
            if (!child) { v=-1; break; }
            v=child;
            path.push_back(v);
        }
        if (op=="COUNT") cout<<(v<0?0:trie[v].terminal)<<'\n';
        else if (op=="PREFIX") cout<<(v<0?0:trie[v].subtree)<<'\n';
        else if (v>=0 && (op=="ADD" || trie[v].terminal>0)) {
            int delta=op=="ADD"?1:-1;
            trie[v].terminal+=delta;
            for (int index:path) trie[index].subtree+=delta;
        }
    }
}
