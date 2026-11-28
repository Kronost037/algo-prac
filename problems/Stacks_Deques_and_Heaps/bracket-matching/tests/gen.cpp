#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    string s(n,'(');
    for (int i=0;i<n;++i) {
        if (mode==1) s[i]="()[]{}"[rnd.next(0,5)];
        if (mode>=2 && i>=n/2) s[i]=')';
    }
    if (mode==3) s.back()=']';
    cout<<s<<'\n';
}
