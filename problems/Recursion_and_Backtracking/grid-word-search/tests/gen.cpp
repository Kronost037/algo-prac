#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<' '<<n<<'\n';
    for(int r=0;r<n;++r) {
        string row(n,'a');
        if (mode==1) for(char& x:row) x=char('a'+rnd.next(0,2));
        if (mode==3 && r==0) row[0]='b';
        cout<<row<<'\n';
    }
    if (mode==0) cout<<"a\n";
    else if (mode==1) cout<<"abcab\n";
    else if (mode==2) cout<<"aaaaaaaaab\n";
    else cout<<"baaaaaaaaa\n";
}
