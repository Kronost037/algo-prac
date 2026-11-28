#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    long long target = opt<long long>(3);
    cout << n << ' ' << target << '\n';
    for (int i = 0; i < n; ++i) {
        int x;
        if (mode == 0) x = 1;
        else if (mode == 1) x = 1000000000;
        else if (mode == 2) x = rnd.next(1, 20);
        else if (mode == 3) x = i % 2 ? 7 : -7;
        else x = i + 2 < n ? -1000000000 : 1000000000;
        cout << x << (i + 1 == n ? '\n' : ' ');
    }
}
