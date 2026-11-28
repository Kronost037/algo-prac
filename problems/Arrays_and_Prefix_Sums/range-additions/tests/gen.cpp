#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), q = opt<int>(2), mode = opt<int>(3);
    cout << n << ' ' << q << '\n';
    for (int i = 1; i <= n; ++i)
        cout << rnd.next(-100, 100) << (i == n ? '\n' : ' ');
    for (int i = 0; i < q; ++i) {
        int l = 1, r = n, x = 1000000000;
        if (mode == 1) {
            l = rnd.next(1, n); r = rnd.next(l, n); x = rnd.next(-100, 100);
        } else if (mode == 2) {
            l = r = i % 2 ? n : 1; x = i % 2 ? -x : x;
        }
        cout << l << ' ' << r << ' ' << x << '\n';
    }
}
