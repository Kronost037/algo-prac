#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), q = opt<int>(2), mode = opt<int>(3);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = mode == 0 ? 0 : mode == 1 ? 2 * i : rnd.next(-20, 20);
    sort(a.begin(), a.end());
    cout << n << ' ' << q << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << (i + 1 == n ? '\n' : ' ');
    const string types[] = {"FIRST", "LAST", "COUNT"};
    for (int i = 0; i < q; ++i) {
        int x = i % 6 < 3 ? a[(i / 6) % n] : rnd.next(-1, 2 * n);
        if (i % 12 >= 9) x = -1000000000;
        cout << types[i % 3] << ' ' << x << '\n';
    }
}
