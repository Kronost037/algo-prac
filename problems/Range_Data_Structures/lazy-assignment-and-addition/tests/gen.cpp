#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), q = opt<int>(2), mode = opt<int>(3);
    cout << n << ' ' << q << '\n';
    for (int i = 1; i <= n; ++i) cout << 0 << (i == n ? '\n' : ' ');
    for (int i = 0; i < q; ++i) {
        if (mode == 0) {
            int l = rnd.next(1, n), r = rnd.next(l, n), op = rnd.next(0, 2);
            if (op == 0) cout << "SUM " << l << ' ' << r << '\n';
            else cout << (op == 1 ? "SET " : "ADD ") << l << ' ' << r << ' '
                      << rnd.next(-1000000, 1000000) << '\n';
        } else if (mode == 1) {
            int m = (n+1)/2;
            switch (i % 8) {
                case 0: cout << "ADD 1 " << n << " 1000000\n"; break;
                case 1: cout << "SET 1 " << m << " 0\n"; break;
                case 2: cout << "ADD " << m << ' ' << n << " -7\n"; break;
                case 3: cout << "SUM 1 " << n << '\n'; break;
                case 4: cout << "SET 1 " << n << " -11\n"; break;
                case 5: cout << "ADD 1 " << m << " 14\n"; break;
                case 6: cout << "SUM " << m << ' ' << m << '\n'; break;
                case 7: cout << "SUM 1 " << n << '\n'; break;
            }
        } else {
            if (i % 5) cout << "ADD 1 " << n << " 1000000\n";
            else cout << "SUM 1 " << n << '\n';
        }
    }
}
