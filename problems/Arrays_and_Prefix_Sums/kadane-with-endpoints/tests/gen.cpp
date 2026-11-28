#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int x = mode == 0 ? -rnd.next(1, 20) : mode == 1 ? 0 :
            mode == 2 ? 1000000000 : mode == 3 ? (i % 2 ? -7 : 7) : rnd.next(-20, 20);
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
}
