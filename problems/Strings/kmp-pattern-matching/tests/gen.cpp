#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=opt<int>(3);
    string s(n,'a'),p(m,'a');
    if (mode==1) {
        for (auto& c:s) c=char('a'+rnd.next(0,25));
        for (auto& c:p) c=char('a'+rnd.next(0,2));
    } else if (mode==3) p.back()='z';
    else if (mode==4) {
        for (int i=0;i<n;++i) s[i]=char('a'+i%26);
        for (int i=0;i<m;++i) p[i]=char('a'+i%26);
    }
    int step=mode==2 ? 1 : mode==4 ? 19 : 31;
    cout<<p<<'\n'<<(n+step-1)/step<<'\n';
    for (int i=0;i<n;i+=step) cout<<s.substr(i,step)<<'\n';
}
