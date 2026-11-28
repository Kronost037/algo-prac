#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    vector<int> a(n+1),st;
    int v=1,value=0;
    while(v<=n||!st.empty()){
        while(v<=n){st.push_back(v);v*=2;}
        v=st.back();st.pop_back();a[v]=++value;v=v*2+1;
    }
    if(mode==1 && n>3)a[4]=a[1]+1;
    if(mode==3 && n>1)a[2]=a[1];
    cout<<n<<'\n';
    for(int i=1;i<=n;++i)cout<<a[i]<<' '<<(2*i<=n?2*i:0)<<' '<<(2*i+1<=n?2*i+1:0)<<'\n';
}
