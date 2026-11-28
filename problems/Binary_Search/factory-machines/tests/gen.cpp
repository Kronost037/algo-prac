#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), t = opt<int>(2), mode = opt<int>(3);
    cout << n << ' ' << t << '\n';
    for (int i = 0; i < n; ++i) {
        int p = mode == 0 ? 1000000000 : mode == 1 ? 1 :
            mode == 2 ? rnd.next(1, 10) : rnd.next(1, 1000000000);
        cout << p << (i + 1 == n ? '\n' : ' ');
    }
}
