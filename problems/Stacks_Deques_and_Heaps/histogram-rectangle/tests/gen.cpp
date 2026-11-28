#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int h = mode == 0 ? 0 : mode == 1 ? 1000000000 : mode == 2 ? i + 1 :
            mode == 3 ? n - i : mode == 4 ? (i % 5 == 4 ? 0 : 9) : rnd.next(0, 1000);
        cout << h << (i + 1 == n ? '\n' : ' ');
    }
}
