#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    string s(n,'a');
    for (int i=0;i<n;++i) {
        if (mode==1) s[i]=char('a'+rnd.next(0,25));
        if (mode==3) s[i]=i%2?'z':'a';
        if (mode==4) s[i]="abacaba"[i%7];
    }
    if (mode==4) s[n/2]='z';
    int q=n<100 ? 100 : 200000;
    cout<<s<<'\n'<<q<<'\n';
    for (int i=0;i<q;++i) {
        int l=1,r=n-i%2;
        if (i%5 || n==1) { l=rnd.next(1,n); r=rnd.next(l,n); }
        cout<<l<<' '<<r<<'\n';
    }
}
