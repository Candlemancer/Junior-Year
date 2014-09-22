/*
 * CS:APP Data Lab
 *
 * Jonathan Petersen
 * A01236750
 *
 * NOTE: Many of these solutions were designed in part using the tricks
 *       available at http://graphics.stanford.edu/~seander/bithacks.html
 *       and http://aggregate.org/MAGIC/. With that said, I affirm that
 *       all of the work in this document is my own creation unless stated
 *       otherwise.
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
   #include <float.h>
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {

  // Uses DeMorgan's law: x & y = ~(~x | ~y)

  return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {

  // This function rightshifts x by n bits, then truncates
  // all but the lowest bit. (x << 3) transforms n into a number
  // of bytes instead of bits.

  int numBits = (n << 3);
  x = x >> numBits;
  return (x & 0xFF);
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {

  // This function creates a mask of length n bits
  // and uses it to erase the leading bits gained
  // by an arithmatic shift.

  // Note: I got some help on this one. http://stackoverflow.com/a/16981120

  int mask = 1;

  mask = mask << 31;
  mask = mask >> n;
  mask = mask << 1;
  mask = ~mask;

  return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {

  // This method for counting bits uses a sieve to accumulate
  // the number of one bits in a 32-bit integer.

  int mask1 = 0x55;
  int mask2 = 0x33;
  int mask3 = 0x0f;

  // Setup the Masks
  mask3 = 0xFF | (0xFF << 16);
  mask3 = mask3 ^ (mask3 << 4);
  mask2 = mask3 ^ (mask3 << 2);
  mask1 = mask2 ^ (mask2 << 1);

  // Binary tree method
  x = x + (~((x >> 1) & mask1) + 1);
  x = (((x >> 2) & mask2) + (x & mask2));
  x = (((x >> 4) + x) & mask3);
  x = x + (x >> 8);
  x = x + (x >> 16);

  return (x & 0x3f);
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {

  // x | ~x + 1 will always have a sign bit of 1, unless
  // x is zero. The x + 1 at the end flips all the ones to
  // zeros.

  int negative = ~x + 1;

  x = (x | negative);
  x = x >> 31;
  x = x + 1;

  return x;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  // Returns the smallest two's complement integer.

  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {

  // Shifts by a mask of size n bits, then XOR's with the
  // sign bit to flip the bits if negative. The bit flipping
  // checks for abs(x) - 1 when x is negative, which mostly
  // handles MIN_INT.

  int numBits = n + ~0;
  int sign = x >> 31;

  return !((x >> numBits) ^ (sign));
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

  // Shifts x by n bits to divide by a power of two,
  // then adds an additional fractional component if
  // x is negative to add one to the result.

  int isNegative = (x >> 31);
  int rounding = isNegative & ((1 << n) + ~0);

  return ((x + rounding)>> n);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

  // Negates x with two's complement.

  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {

  // If the sign of x is negative (1), then x(0) | notX(1) will be 0x1.
  // If the sign of x is positive (0), then x(0) | notX(0) will be 0x0.
  // If x is zero, then x(0) | notX(1) will be 0x1.
  // This funciton returns the opposite of that.

  int notX = !x;

  x = x >> 31;
  x = x | notX;
  x = !x;

  return x;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

  // This function returns 1 if x <= y, otherwise it returns 0.
  // It calculates the difference between the two numbers, and then
  // combines the sign of that value with the signs of the two numbers.

  int highX = x >> 31;
  int highY = y >> 31;
  int result = 0;
  int sign = 0;

  // If the signs are the same, then the sign of x - y will be negative (1).
  // If the signs are different, then the negative one is smaller.
  sign = !(highX ^ highY);
  result = sign & ((x + ~y) >> 31);
  result = result | ((!highY) & highX);

  return result;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

  // This funcitons computes the log base 2 of x. It starts
  // by propogating the highest one bit all the way right then concludes
  // by counting the number of ones. Because of the way binary works,
  // this is the log_2(x).

  int mask1 = 0x55;
  int mask2 = 0x33;
  int mask3 = 0x0f;

  //Propogate the high bit
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);

  x = (x >> 1);

  // Setup the counting Masks
  mask3 = 0xFF | (0xFF << 16);
  mask3 = mask3 ^ (mask3 << 4);
  mask2 = mask3 ^ (mask3 << 2);
  mask1 = mask2 ^ (mask2 << 1);

  // Binary tree method to count bits
  x = x + (~((x >> 1) & mask1) + 1);
  x = (((x >> 2) & mask2) + (x & mask2));
  x = (((x >> 4) + x) & mask3);
  x = x + (x >> 8);
  x = x + (x >> 16);

  return (x & 0x3f);
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

  // This function will return a float with the sign bit toggled.
  // If the input is NaN, it returns NaN. It checks for NaN by
  // discarding the sign bit and checking if the the exponent bits
  // are all set and the mantissa is greater than zero.

  // Discard the sign bit while checking for NaN.
  unsigned int val = uf << 1;

  // If the number is greater than all of the exponent bits set,
  // it must be NaN.
  if (val > 0xFF000000) {
    return uf;
  }

  // Flip the sign bit and return.
  return (uf ^ 0x80000000);
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {

  // This function is a thing. After dealing with error cases, it records the
  // sign bit and insures the value of the int is positive. Then it moves the
  // most significant one to the higest bit location to calculate how large
  // the exponent should be. The remaining value is then divided down into a
  // mantissa, and the result is then rounded appropriately.

  // Note: Adapted from a solution at http://pastie.org/pasties/6001301

  unsigned int f = x;
  unsigned int signMask = 0;
  unsigned int exponent = 158; // 127(Float Bias) + 31(Max Shifts)
  unsigned int mantissa = 0;
  unsigned int guardBit = 0;
  unsigned int roundBit = 0;

  // If the int is 0, return 0.
  if (x == 0) {
    return 0;
  }

  // If the number's negative, flip the sign bit and make it positive.
  if (x < 0) {
    signMask = 0x80000000;
    f = -x;
  }

  // Bring the most significant 1 to the high bit,
  // adjusting the exponent for each shift.
  while ((f & 0x80000000) == 0) {
    f = f << 1;
    exponent = exponent - 1;
  }
  mantissa = f << 1;

  // Setup the rounding scheme and move things to their proper place.
  guardBit = (mantissa & 0x00000200) >> 9;
  roundBit = (mantissa & 0x000001FF);
  mantissa = mantissa >> 9;
  exponent = exponent << 23;

  // Calcluate answer
  f = signMask | exponent | mantissa;

  //Adjust answer if you need to round.
  if (roundBit  > 0x00000100 ||
     (roundBit == 0x00000100 && guardBit)) {
    f = signMask + (exponent + mantissa + 1);
  }

  return f;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

  // This function separates a float into its component bit segments,
  // then it adds one to the exponent, effectively multiplying the
  // float by two. If there is no exponent, it simply multiplies the
  // mantissa by two.

  unsigned int signMask = 0;
  unsigned int exponent = 0;
  unsigned int mantissa = 0;

  signMask = (0x80000000 & uf);
  exponent = (0x7F800000 & uf);
  mantissa = (0x007FFFFF & uf);

  // If the float is NaN or Infinity, return the float.
  if (exponent == 0x7F800000) {
    return uf;
  }

  // I don't know why this if is needed, but it works.
  if (exponent != 0) {
    exponent = exponent + (0x00800000);
  }
  else {
    mantissa = mantissa * 2;
  }

  return (signMask | exponent | mantissa);
}
