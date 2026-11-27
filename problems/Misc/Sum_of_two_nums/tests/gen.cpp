#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = rnd.next(INT_MIN, INT_MAX);
    int b = rnd.next(INT_MIN, INT_MAX);

    cout << a << " " << b << '\n';
    return 0;
}