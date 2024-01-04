#include<bits/stdc++.h>
using namespace std;

int main(){
    int x=0x7FFFFFFF;;
    if(x+1) cout<<1<<endl;
    for(x=-0x80000000;x<=0x7FFFFFFF;x++){
        int a=!((~(x+1))^x);
        int b=!!(x+1);
        if(a&b) cout<<"sb "<<x<<endl;
    }
}