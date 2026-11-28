#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum = 0, assignment = 0, addition = 0;
    bool assigned = false;
};

class Tree {
    vector<Node> t;
    void build(int v, int l, int r, const vector<long long>& a) {
        if (l == r) { t[v].sum = a[l]; return; }
        int m = (l + r) / 2;
        build(2*v, l, m, a);
        build(2*v+1, m+1, r, a);
        pull(v);
    }
    void pull(int v) { t[v].sum = t[2*v].sum + t[2*v+1].sum; }
    void set(int v, int length, long long x) { t[v] = {length*x, x, 0, true}; }
    void add(int v, int length, long long x) {
        t[v].sum += length*x;
        t[v].addition += x;
    }
    void push(int v, int leftLength, int rightLength) {
        auto& node = t[v];
        if (node.assigned) {
            set(2*v, leftLength, node.assignment);
            set(2*v+1, rightLength, node.assignment);
            node.assigned = false;
        }
        if (node.addition != 0) {
            add(2*v, leftLength, node.addition);
            add(2*v+1, rightLength, node.addition);
            node.addition = 0;
        }
    }
public:
    explicit Tree(const vector<long long>& a) : t(4*a.size()) {
        build(1, 0, int(a.size()) - 1, a);
    }
    long long apply(int v, int l, int r, int ql, int qr, const string& op, long long x) {
        if (ql <= l && r <= qr) {
            if (op == "SET") set(v, r-l+1, x);
            else if (op == "ADD") add(v, r-l+1, x);
            return t[v].sum;
        }
        int m = (l + r) / 2;
        push(v, m-l+1, r-m);
        long long answer = 0;
        if (ql <= m) answer += apply(2*v, l, m, ql, qr, op, x);
        if (qr > m) answer += apply(2*v+1, m+1, r, ql, qr, op, x);
        pull(v);
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    Tree tree(a);
    while (q--) {
        string op;
        int l, r;
        long long x = 0;
        cin >> op >> l >> r;
        if (op != "SUM") cin >> x;
        long long answer = tree.apply(1, 0, n-1, l-1, r-1, op, x);
        if (op == "SUM") cout << answer << '\n';
    }
}
