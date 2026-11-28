#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    cout<<n<<'\n';
    const string ops[]={"ADD","ADD","PREFIX","ERASE","COUNT","PREFIX","ERASE","COUNT"};
    for (int i=0;i<n;++i) {
        int length=n<100?rnd.next(1,8):2;
        string w(length,'a');
        for (char& c:w) c=char('a'+(mode==2?0:rnd.next(0,mode==3?25:2)));
        if (n>=100 && i%8==2) w.resize(1);
        cout<<ops[i%8]<<' '<<w<<'\n';
    }
}
