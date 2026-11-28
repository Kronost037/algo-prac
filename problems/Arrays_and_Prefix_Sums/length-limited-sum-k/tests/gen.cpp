#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), low = opt<int>(2), high = opt<int>(3), mode = opt<int>(4);
    int k = mode == 2 ? 1000000000 : mode == 3 ? rnd.next(-10, 10) : 0;
    cout << n << ' ' << low << ' ' << high << ' ' << k << '\n';
    for (int i = 0; i < n; ++i) {
        int x = mode == 0 ? 0 : mode == 1 ? (i % 2 ? -1 : 1)
            : mode == 2 ? 1000000000 : rnd.next(-10, 10);
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
}
