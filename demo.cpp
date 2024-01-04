#include <bits/stdc++.h>
using namespace std;


void solve(){
    int x, y;
    while(cin >> x >> y){
        cout << ~((~(x&~y))&(~(~x&y))) << endl;
        cout <<( x^y )<< endl;
    }
}

int main (){
    solve();
}