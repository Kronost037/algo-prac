#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=opt<int>(3);
    string a(n,'a'),b(m,mode==3?'z':'a');
    if(mode==1) {
        for(char& c:a) c=char('a'+rnd.next(0,4));
        for(char& c:b) c=char('a'+rnd.next(0,4));
    }
    if(mode==4) {
        for(int i=0;i<n;++i) a[i]=i%2?'a':'z';
        for(int i=0;i<m;++i) b[i]=i%2?'z':'a';
    }
    cout<<a<<'\n'<<b<<'\n';
}
