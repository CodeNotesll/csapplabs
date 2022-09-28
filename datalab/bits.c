/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int a = ~x & y;
  int b = x & ~y;
  return ~(~a & ~b);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int a = 1;
  //printf("sizeof(int) is %d\n", sizeof(int)); 4 
  return a << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
// ~(Tmax+1) = x tmax 
int isTmax(int x) {
  // int b = !(~x);// should be zero; eliminate -1 
  // int a = ((~(x+1))^x); // should be zero; 
  // return !(b|a);
  return (!!(~x)) & !((~(x+1))^x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // int a = ~x; // say x is 1_1_,1_1_; ~x is 0_0_,0_0_
  // int b = 0xaa;            // ~x & (10101010) -> 0;
  // int c1 = a&b;
  // int c2 = (a>>8)&b; 
  // int c3 = (a>>16)&b; 
  // int c4 = (a>>24)&b;  
  // return !(c1 | c2 | c3 | c4); 
  int b = ~x;
  int aa = 0xaa;
  int aaaa = aa | (aa << 8);
  int mask = aaaa | (aaaa << 16);
  return !(mask & b);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int f) {
  #if 0
  int high = f >> 8; // should be 0 
  int mid = (f >> 4)^0x3; // should be 0   
  int x = (f>>3)&0x1;
  int y = (f>>2)&0x1;
  int z = (f>>1)&0x1;
  int lowans = x&(y|z); // should be 0
  return !(high | mid | lowans);
  #endif 
  
  int high = f >> 8; // should be 0 
  int mid = (f >> 4)^0x3; // should be 0   
  int a = 0xa;
  int c = f&0xf;
  c = c + (~a + 1); // should < 0
  //return !high & !mid & (!!(c >> 31));
  return !(high | mid | !(c>>31));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
// c&y | (~c)&z;
// 1 + (-1) = 0x000..0
// 0 + (-1) = 0xfff..f
int conditional(int x, int y, int z) {
  int c = !x + (~0); // if x == 0 c == 0x0; else c = 0xff.ff
 // if x is 0, then c is 0000...0000, return z 
 // if x != 0, then c is ffff...ffff, return y
  return (c&y) | ((~c)&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  #if 0
  int z = x + (~y + 1);  // get x - y
  //x is zero or negative
  int hx = (x >> 31)&0x1;  // sign number 1 or 0
  int hy = (y >> 31)&0x1;  // sign number 1 or 0
  int hz = (z >> 31)&0x1;  // sign number 1 or 0
  int h = !(z^0x0);  // should be 
  //  may underflow 
  // x is negetive, y is pos, and e is pos
 // int j = !((!hx) |  hy | hz);
  int j = hx & !hy & !hz;  // should be 1 
  // may overflow x is pos, y and z is negative
  //int k = (!(x>>31)) & (!!(y>>31)) & (!!(z>>31));
  int k = (!hx) & (hy) & (hz); // should be 0 
  return ((h | hz | j)) & !k;
  #endif
  #if 1
  int eq = !(x^y);   // if x == y eq = 1
  int sx = (x>>31)&0x1;
  int sy = (y>>31)&0x1;
  // sx is 0, sy is 1
  int x_p_y_n = sx|(!sy);  
  // sx is 1, sy is 0
  int x_n_y_p = sx&(!sy);
  //sx and sy same sign
  int res = x+(~y + 1); // won't overflow or underflow
  res = (res>>31)&0x1; // should be 1
  return eq |(x_p_y_n & ( x_n_y_p | res ));
  #endif 
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  
  int sign1, sign2;
  sign1 = ((x >> 31)&0x1)^0x1; 
  x = (~x) + 1;
  sign2 = ((x >> 31)&0x1)^0x1; 
  // sign1 is 0 then x is negative
  // sign1 is 1, (x zero or positive); sign2 is 0, then x is positive;
  return sign1 & sign2;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
// 32 (0000,002d) and 45(0000,0020) requires same number(7) of bits to represent
// -5 (ffff,fffb) and -3(ffff,fffd) requires same number(4) of bits to represent
int howManyBits(int x) {
  // if x >=0, y is 00..0, else y is 1111..111
  int pos, mask0, mask1, mask2, mask4,
   mask8, mask16, res;
  int y = (x >> 31);
  x = x ^ y; // x > 0
  // x = (y&(~x)) | (~y &x); 
  // find the highest pos of  1 
  pos = 1;
  mask0 = 0x01;
  mask1 = 0x02;   // 0x02
  mask2 = 0x0c;   // 0x0c
  mask4 = 0xf0;   // 0xf0
  mask8 = (0xff << 8); // 0xff00
  mask16 = (0xff << 24) | (0xff << 16); // 0xffff0000
  // highest 16 bits, 16~31
  res = !!(x&mask16);  // 1 if there're 1 in high 16 bits 
  pos = pos + (res << 4);
  x = x >> (res << 4);

  //highest 8 bits, 8~15
  res = !!(x&mask8);
  pos = pos + (res << 3);
  x = x >> (res << 3);

  // highest 4 bits, 4 ~7
  res = !!(x&mask4);
  pos = pos + (res << 2);
  x = x >> (res << 2);

  // highest 2 bits, 2 ~3
  res = !!(x&mask2);
  pos = pos + (res << 1);
  x = x >> (res << 1); 

  // highest 1 bits,  1
  res = !!(x&mask1);
  pos = pos + res ;
  x = x >> res;  

  // check LSB 0
  res = x&mask0;
  pos = pos + res;
  
  return pos;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp = (uf>>23)&0xff;
  int mask = (((0x7f << 8)|0xff)<<8)|0xff;
  int m   = uf&mask;
  int inf_or_Nan = (!(exp^0xff)); 
  // if exp == 0xff 
  if(inf_or_Nan) { // Nan
    return uf;
  }
  if (!exp) { // exp is 0x00
    return (m << 1) + ((uf >> 31) << 31);
  }
  // exp != 0
  exp = exp + 1;
  if (!(exp^0xff)) { // exp == 0xff
    return ((uf>>31)<<31) + (exp << 23); // overflow
  }
  return uf + (1<<23);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {

  int less_23, above_30;
  int upper =   0x80 << 24;
  int sign  =   uf >> 31;// 000.001 or 000.0000
  int E     =   (uf >> 23)&0xff;
  int mask  =   (((0x7f << 8)|0xff)<<8)|0xff;
  int m     =   (1 << 23) + (uf&mask);
  int exp   =   E - 0x7f;
  if(exp >> 31) { // exp < 0, underflow
    return 0;
  }
  // if (exp < 0) {   // compare operators allowed 
  //   return 0;
  // }
  less_23 =  23 - exp; // 23 - exp
  above_30 = exp - 30;
  if (!((!above_30)|(above_30 >> 30))) { // exp > 30
      return upper;
  }
  // if (above_30 > 0) {
  //   return upper;
  // }
  if (!(less_23>>31)) { //23 - exp >= 0
    m = m >> less_23;
  }
  // if (less_23 >= 0) {
  //   m = m >> less_23;
  // }
  else {  // exp > 23
       m = m << (exp - 23);
  }
  mask = (sign << 31) >> 31; // if sign is 1, mask is 1111.111
  m = m^mask;  // flip if sign is 1
  m = m + sign; // and plus 1, if sign is 1
  return m;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */

// 2^x > 0
// 2^(-126)*2^(-23)
unsigned floatPower2(int x) {
  int inf = 0xff << 23;
  if (x > 127) {
    return inf;
  }
  if (x <= -150) { 
    return 0;
  }
  if (x <= -127) { // 2^(-126)*(2^(e))
    int f = 0x7e;
    int num = (~f + 1) - x; // -126 - x
    return (1 << (23-num));
  }
  return (x + 127) << 23; // -126 <= x <= 127
  //return 0;
}
