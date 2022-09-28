#line 145 "bits.c"
int bitXor(int x, int y) {
  int a=  ~x & y;
  int b=  x & ~y;
  return ~(~a & ~b);
}
#line 156
int tmin(void) {
  int a=  1;

  return a << 31;
}
#line 170
int isTmax(int x) {
#line 174
  return (!!(~x)) & !((~(x+1))^x);
}
#line 184
int allOddBits(int x) {
#line 192
  int b=  ~x;
  int aa=  0xaa;
  int aaaa=  aa |( aa << 8);
  int mask=  aaaa |( aaaa << 16);
  return !(mask & b);
}
#line 205
int negate(int x) {
  return ~x + 1;
}
#line 218
int isAsciiDigit(int f) {
  int high=  f >> 8;
  int mid=(  f >> 4)^0x3;
#line 226
  int a=  0xa;
  int c=  f&0xf;
  c = c +( ~a + 1);

  return !(high | mid | !(c>>31));
}
#line 242
int conditional(int x, int y, int z) {
  int c=  !x +( ~0);


  return (c&y) |(( ~c)&z);
}
#line 255
int isLessOrEqual(int x, int y) {
#line 273
  int eq=  !(x^y);
  int sx=(  x>>31)&0x1;
  int sy=(  y>>31)&0x1;

  int x_p_y_n=  sx|(!sy);

  int x_n_y_p=  sx&(!sy);

  int res=  x+(~y + 1);
  res =( res>>31)&0x1;
  return eq |(x_p_y_n &(  x_n_y_p | res));

}
#line 295
int logicalNeg(int x) {

  int sign1;int sign2;
  sign1 =(( x >> 31)&0x1)^0x1;

  x =( ~x) + 1;
  sign2 =(( x >> 31)&0x1)^0x1;


  return sign1 & sign2;
#line 310
}
#line 326
int howManyBits(int x) {

  int pos;int mask0;int mask1;int mask2;int mask4;int 
   mask8;
#line 328
  int 
          mask16;
#line 328
  int 
                  res;
  int y=(  x >> 31);
  x = x ^ y;


  pos = 1;
  mask0 = 0x01;
  mask1 = 0x02;
  mask2 = 0x0c;
  mask4 = 0xf0;
  mask8 =( 0xff << 8);
  mask16 =( 0xff << 24) |( 0xff << 16);

  res = !!(x&mask16);
  pos = pos +( res << 4);
  x = x >>( res << 4);

  res = !!(x&mask8);
  pos = pos +( res << 3);
  x = x >>( res << 3);


  res = !!(x&mask4);
  pos = pos +( res << 2);
  x = x >>( res << 2);


  res = !!(x&mask2);
  pos = pos +( res << 1);
  x = x >>( res << 1);


  res = !!(x&mask1);
  pos = pos + res;
  x = x >> res;


  res = x&mask0;
  pos = pos + res;

  return pos;
}
#line 383
unsigned floatScale2(unsigned uf) {
  int exp=(  uf>>23)&0xff;
  int mask=(((  0x7f << 8)|0xff)<<8)|0xff;
  int m=  uf&mask;
  int inf=(  !(exp^0xff));

  if (inf) {
    return uf;
  }
  if (!exp) {
    return (m << 1) +(( uf >> 31) << 31);
  }

  exp = exp + 1;
  if (!(exp^0xff)) {
    return ((uf>>31)<<31) +( exp << 23);
  }
  return uf +( 1<<23);
}
#line 414
int floatFloat2Int(unsigned uf) {

  int less_23;int above_30;
  int upper=  0x80 << 24;
  int sign=  uf >> 31;
  int E=(  uf >> 23)&0xff;
  int mask=(((  0x7f << 8)|0xff)<<8)|0xff;
  int m=(  1 << 23) +( uf&mask);
  int exp=  E - 0x7f;
  if (exp>> 31) {
    return 0;
  }
#line 429
  less_23 = 23 - exp;
  above_30 = exp - 30;
  if (!((!above_30)|(above_30 >> 30))) {
      return upper;
  }
#line 437
  if (!(less_23>>31)) {
    m = m >>less_23;
  }
#line 443
  else {
       m = m <<( exp - 23);
  }
  mask =( sign << 31) >> 31;
  m = m^mask;
  m = m + sign;
  return m;
}
#line 467
unsigned floatPower2(int x) {
  int inf=  0xff << 23;
  if (x > 127) {
    return inf;
  }
  if (x <= -150) {
    return 0;
  }
  if (x <= -127) {
    int f=  0x7e;
    int num=(  ~f + 1) - x;
    return (1 <<( 23-num));
  }
  return (x + 127) << 23;

}
