#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt<int>(1), mode = opt<int>(2);
    int m=opt<int>(3),q=n<50?90:200000;
    cout<<n<<' '<<m<<' '<<q<<'\n';
    vector<pair<int,int>>cells;
    for(int r=0;r<n;++r){
        for(int c=0;c<m;++c){
            char x='.';
            if(mode==1){int z=rnd.next(1,10);x=z<=3?'#':z==4?'S':'.';}
            if(mode==2 && (r==0&&c==0 || r==n-1&&c==m-1))x='S';
            if(mode==3 && c==m/2 && c>0)x='#';
            if(r==0&&c==0)x=mode==0?'.':'S';
            if(x!='#')cells.emplace_back(r+1,c+1);
            cout<<x;
        }
        cout<<'\n';
    }
    for(int i=0;i<q;++i){auto [r,c]=cells[rnd.next(int(cells.size()))];cout<<r<<' '<<c<<'\n';}
}
