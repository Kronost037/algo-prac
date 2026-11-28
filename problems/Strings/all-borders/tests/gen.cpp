#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    string s(n,'z');
    for (int i=0;i<n;++i) {
        if (mode==1) s[i]=char('a'+rnd.next(0,25));
        if (mode==2) s[i]=char('a'+i%26);
        if (mode==4) s[i]="abacaba"[i%7];
    }
    if (mode==3) s.back()='a';
    cout<<s<<'\n';
}
