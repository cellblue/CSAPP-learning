#include<bits/stdc++.h>
using namespace std;
int isAsciiDigit(int x) {
  int y;
  x=x+2;
  y=(!((x^48)>>3));
  y=y|(!(x^56))|(!(x^57));
  return y;
}

int mconditional(int x, int y, int z) {
  int a=y,b=z;
  return  *(&a+(!x));
}
int isLessOrEqual(int x, int y) {
  int a,b,c;
  a=x;
  b=(~y)+1;
  c=a+b;
  return ((c>>31&1)&(!((!(a>>31))&(y>>31))))|(!(c^0))|((!(y>>31))&(a>>31));
}

int logicalNeg(int x) {
  int mx=0xff;
  mx=mx<<8|mx;
  mx=mx<<16|mx;
  return ((((((x^(1<<31)))+mx)>>31)&1)|(x>>31&1))^1;
}

int howManyBits(int x) {
  int r=31,l=0,mid,op,z,zz,tmp,m,n;
  op=x>>31&1;
  op=(~(!op))+1;
  zz=(((~x)+1)&(~op))+(x&op);
  tmp=x;
  x=zz;
  zz=tmp;

  mid=r+l>>1;
  op=x>>mid;
  op=(~(!op))+1;
  z=~op;
  l=(mid+1&(z))+(l&op);
  r=(r&(z))+(mid&op);

  mid=r+l>>1;
  op=x>>mid;
  op=(~(!op))+1;
  z=~op;
  l=(mid+1&(z))+(l&op);
  r=(r&(z))+(mid&op);

  mid=r+l>>1;
  op=x>>mid;
  op=(~(!op))+1;
  z=~op;
  l=(mid+1&(z))+(l&op);
  r=(r&(z))+(mid&op);

  mid=r+l>>1;
  op=x>>mid;
  op=(~(!op))+1;
  z=~op;
  l=(mid+1&(z))+(l&op);
  r=(r&(z))+(mid&op);

  mid=r+l>>1;
  op=x>>mid;
  op=(~(!op))+1;
  z=~op;
  l=(mid+1&(z))+(l&op);
  r=(r&(z))+(mid&op);

  m=!(x^(1<<l>>1));
  n=zz>>31&1;
  return l+!(m&n);
}

unsigned floatScale2(unsigned uf) {
  unsigned mx=0xff,os=(uf<<1)>>24,ta,op,tmp;
  ta=(uf<<9>>9);
  if(os==mx) return uf;
  if(os!=0){
    ta=ta|1<<23;
  }
  ta=ta+ta;
  if(ta>>24&1){
    ta=(ta^(1<<24))>>1;
    os=os+1;
  }
  tmp=0x80;
  tmp=tmp<<1;
  tmp=tmp<<23;
  uf=uf&tmp;
  uf=uf|(os<<23)|ta;
  return uf;
}

int main(){
    unsigned x=0x3f800000;
    cout<<floatScale2(x)<<endl;
    return 0;
}