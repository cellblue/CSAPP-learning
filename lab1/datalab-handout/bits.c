/* 
 * CS:APP Data Lab 
 * 
 * lancee
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
  // 先画个真值表，之后德摩根定律化简一下
  // 就直接7操作数了
  return (~(~x&~y))&(~(x&y));
}
/* 
 * tmin - return minimum two's complement integer 
 * 最小二进制补码整数
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 这个不行，右移是算术右移
  //return (~0)^((~0)>>1);
  return (1 << 31);
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // 判断当前数是否为0111111...或者为11111...
  int judge1 = !((x+1)^(~x));
  // 如果为11111...则不满足条件
  int judge2 = !!(x+1);
  // 成功有可移植特征！！！
  return judge1 & judge2;
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
  // 一目了然
  int y = 0xAA + (0xAA << 8) + (0xAA << 16) + (0xAA << 24);
  return !((y&x)^y);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 负数补码，取反+1
  return ((~x)+1);
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
int isAsciiDigit(int x) {
  // 得加最外层这个括号，不能像下面这样
  // return (!((x >> 4) ^ 3)) & (!!(x&8)&!((x&4)|(x&2)))|!(x&8);
  // 正确如下
  // 判断除了低四位外，高位有且仅有5 6位为1
  int judge1 = !((x >> 4) ^ 3);
  // 判断低四位是否在1001之内
  int judge2 =  (!!(x&8)&!((x&4)|(x&2)))|!(x&8);
  return judge1 & judge2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 首先判断是否为0
  int judge1 = !!x;
  // 天才的想法把1转换为11111....
  // 0就转换为0 最后与完或一下就行了
  int judge2 = (((~judge1)+1)&y) | ((~((~judge1)+1))&z);
  return judge2;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int xx = x >> 31;
  int yy = y >> 31;
  // 判断异号的情况，在同号的情况下做减法(y + (~x) + 1)判断是否溢出
  return ((xx & (!yy)) | (!((y + (~x) + 1) >> 31))) & !((!xx) & yy);
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
  // 取最后一位的一，格式为0000100000，仅包含一个1
  int judge1 = (x & ((~x) + 1));
  // 取反+1，如果为0，+1后会溢出，则最高位为0，如果不为0，最高位为1
  // 将结果+1后&1即可得出答案
  int judge2 = ((((~judge1) + 1) >> 31) + 1) & 1;
  return judge2;
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
int howManyBits(int x) {
//   // 首先判断是否是负数
//   int judge1 = ((x >> 31) & 1);
//   // 负数的话取反+1
//   int _x = (~x)+1;
//   // 如果负数取反+1，如果不是负数则不用
//   int true_x = (((~judge1)+1)&_x) | ((~((~judge1)+1))&x);
//   // 判断最高位的1是第几个
//   int top = 1 << 31;
//   int add_31 = !!(top & true_x);
//   int add_30 = !!((top>>1) & true_x) + add_31;
//   int add_29 = !!((top>>2) & true_x) + add_30;
//   int add_28 = !!((top>>3) & true_x) + add_29;
//   int add_27 = !!((top>>4) & true_x) + add_28;
//   int add_26 = !!((top>>5) & true_x) + add_27;
//   int add_25 = !!((top>>6) & true_x) + add_26;
//   int add_24 = !!((top>>7) & true_x) + add_25;
//   int add_23 = !!((top>>8) & true_x) + add_24;
//   int add_22 = !!((top>>9) & true_x) + add_23;
//   int add_21 = !!((top>>10) & true_x) + add_22;
//   int add_20 = !!((top>>11) & true_x) + add_21;
//   int add_19 = !!((top>>12) & true_x) + add_20;
//   int add_18 = !!((top>>13) & true_x) + add_19;
//   int add_17 = !!((top>>14) & true_x) + add_18;
//   int add_16 = !!((top>>15) & true_x) + add_17;
//   int add_15 = !!((top>>16) & true_x) + add_16;
//   int add_14 = !!((top>>17) & true_x) + add_15;
//   int add_13 = !!((top>>18) & true_x) + add_14;
//   int add_12 = !!((top>>19) & true_x) + add_13;
//   int add_11 = !!((top>>20) & true_x) + add_12;
//   int add_10 = !!((top>>21) & true_x) + add_11;
//   int add_9 = !!((top>>22) & true_x) + add_10;
//   int add_8 = !!((top>>23) & true_x) + add_9;
//   int add_7 = !!((top>>24) & true_x) + add_8;
//   int add_6 = !!((top>>25) & true_x) + add_7;
//   int add_5 = !!((top>>26) & true_x) + add_6;
//   int add_4 = !!((top>>27) & true_x) + add_5;
//   int add_3 = !!((top>>28) & true_x) + add_4;
//   int add_2 = !!((top>>29) & true_x) + add_3;
//   int add_1 = !!((top>>30) & true_x) + add_2;
//   int add_0 = !!((top>>31) & true_x) + add_1;
//   int judge2 = judge1 & (!(true_x & (true_x + (~0))));
//   return add_0 + 1 + ((~judge2) + 1);
// 180
  // 上面这种做法操作数为180，但是能过，
  // 下面是优化写法
  int is_neg = (x >> 31);
  // 一个神奇的写法，我之前一直默认是直接取一个最高位的0或者1，但其实为算数右移
  // 想到 is_neg 是算数右移后，这种判断写法很简单了
  // 如果x是负数则不需要对～x进行+1，比如特例-2^n这种类型的数字
  // 如果+1了还需要在最后进行特判一下, 不加就不用特判
  int pos_x = ((~is_neg) & x) | (is_neg & (~x));

  int b16,b8,b4,b2,b1,b0;
  // 下面介绍的是神奇二分写法
  b16 = (!!(pos_x >> 16)) << 4;
  pos_x = pos_x >> b16;
  b8 = (!!(pos_x >> 8)) << 3;
  pos_x = pos_x >> b8;
  b4 = (!!(pos_x >> 4)) << 2;
  pos_x = pos_x >> b4;
  b2 = (!!(pos_x >> 2)) << 1;
  pos_x = pos_x >> b2;
  b1 = (!!(pos_x >> 1));
  pos_x = pos_x >> b1;
  b0 = pos_x;
  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
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
  unsigned s = (uf >> 31) & 1;
  unsigned exp = (uf >> 23) & (0xff);
  unsigned frac = (s << 31) ^ (exp << 23) ^ uf;
  // 当NaN时返回NaN
  if(exp == 0xff){
    return uf;
  }
  // 如果是规格数，则阶码直接+1，如果是非规格数则尾数相加
  if(exp != 0){
    exp = exp + 1;
  }else {
    frac = frac + frac;
  }
  // 这里就算 非规格化尾数相加，尾数溢出也会加到阶码上
  return (s<<31) + (exp<<23) + frac;
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
// 1/2 0 01111110 000000
int floatFloat2Int(unsigned uf) {
  unsigned s = (uf >> 31) & 1;
  unsigned exp = (uf >> 23) & (0xff);
  unsigned frac = (s << 31) ^ (exp << 23) ^ uf;
  if(exp < 127) {
    return 0;
  }
  if(exp > 158 || (exp == 158 && (!!frac))) {
    return 0x80000000u;
  }
  // 将默认的1加上
  frac = frac | (1 << 23);
  // 如果大于23位左移
  if(exp - 127 >= 23){
    frac = frac << (exp - 127 - 23);
  } else {
    // 小于则右移
    frac = frac >> (127 + 23 - exp);
  }
  // 如果是负数则取反
  if(s == 1){
    frac = (~frac) + 1;
  }
  return frac;
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
unsigned floatPower2(int x) {
  if(x < -126) {
    return 0;
  }
  if(x > 127) {
    return 0xff<<23;
  }
  x = x + 127;
  return (x << 23);
}
