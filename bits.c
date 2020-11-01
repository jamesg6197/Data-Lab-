/* 
 * CS:APP Data Lab 
 * 
 * <James Guo 505574712>
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~ (~x | ~y); //DeMorgan's Laws
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
  // bytes are 8 bits so we have to multiple n by 8 and shift x by 8*n
  //  & result with 255 gives the last two bytes
  return ((x >> (n << 3)) & 255); 

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops:  !  ~  & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  // shift right n units
  // mask out the most significant n bits
  return (x >> n) & ~(((~1 + 1) << ((~n + 1) + 31)) << 1 );
}
/* 
 * rotateRight - Rotate x to the right by n
*   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  // left shift n units and add the discarded bits to the front
  int vector = ((x << (31 + ((~n) + 1))) << 1); // discarded n bits
  int mylogicalshift = (x >> n) & ~(((~1 + 1) << ((~n + 1) + 31)) << 1); // left shift
  return (vector + mylogicalshift); // Combine
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // if x is 0, do z, else do y
  return (((!x << 31 >> 31) & z ) + (((!!x) << 31 >> 31) & y)); // !0 is 1 and <<31>>31 makes it a vector of 1s do return z.
   // !!0 is 0 and 1 for anything else so we do the same strategy as before
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int zerodif = (x | (~x + 1)); // if x == 0, -x will equal 0, but  x | ~x + 1 will be negative(leading 1) for x != 0
  zerodif = (~ zerodif) >> 31; //flip the numbers so that will always start with 1, and all else will start with 0.
				//push the msb to the back
  return zerodif & 1; // returns the last bit (1 for x == 0, 0 for x != 0)
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  //We need to compare XOR every bit in the int. If it returns 1, there is an odd number of 0s.
  //8 Bit Example: [x0,x1, x2, x3, x4, x5, x6, x7]
  //[x4 ^ x0, x5 ^ x1, x6 ^ x2, x7 ^ x3]
  //[x6 ^ x2 ^ x4 ^ x0, x7 ^ x3 ^ x5 ^ x1]
  //[x7 ^ x3 ^ x5 ^ x1 ^ x6 ^ x2 ^ x4 ^ x0] 
  int first = (x >> 16) ^ x;
  int second = (first >> 8) ^ first;
  int third = (second >> 4) ^ second;
  int fourth = (third >> 2) ^ third;
  int fifth = (fourth >> 1) ^ fourth;
  return fifth & 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | + 
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
   int plusOne = x + 1; //max + 1 is min
   return !(~(x + plusOne) | !plusOne); //if x == tmax, then x + x + 1 is all ones. The !plusOne takes care of when x == -1
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
  return !(((x << (32 + (~n + 1))) >> (~n + 1)) ^ x); // x can only fit in n bits if the most significant 32 - n bits are all 1 or 0s
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
    // >> inherently rounds towards negative infinity for signed ints but floors unsigned ints
    int negcheck = (x >>  31) & 1; // check if x < 0. Returns 1 if it is
    return (x + (negcheck << n) + (~(negcheck) + 1) ) >> n; //To round toward zero we must add 2^n - 1, and then shift
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x + 1); //definition of negate
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return (!(x & (1 << 31)) & (!!x)); //If msb is 1 then it's negative. !!x takes care of when x == 0.
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int z = x + (~y + 1); // find the difference of x and y
  int checkmsb = !(z >> 31) & 1; //returns 1 if the difference is positive, 0 if negative
  // Overflows only when x and y have opposite sides
  int signx = (x >> 31) & 1; // get sign of x
  int signy = (y >> 31) & 1; // get sign of y
  int signcheck = !(signx ^ signy); // returns 1 if they are the same sign
  return ((signcheck & checkmsb) | (!signcheck & !signx)) & (!!z); // check difference only if the signs are the same
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int signx = (x >> 31) & 1; // returns 1 if negative, 0 if positive
  int signy = (y >> 31) & 1; // returns 1 if negative, 0 if positive
  int signcheck = (signx ^ signy); // returns 1 if the signs are difference, overflow cannot happen if both x and y have the same signs
  int difference = x + (~y + 1); // computes x-y
  int signdifference = (difference >> 31) & 1; //sign of the difference (accounts for overflow)
  return ((!signcheck) | (!(((!signx) & signdifference) | (signx & (!signdifference))))); // if the sign of the difference is different from the sign of x, overflow happens.
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  // The log of x is the position of the most significant bit. (Could have shortened the amount of bits but for some reason it wouldn't let me use declared variables).
  int count = 0;
  // binary search method
  count = count + (((~(!!(x >> 16))) + 1) & 16); //If there is a one in the most significant 16 bits, push 16 to the right and add 16 to count , else do nothing
  x = x >> (((~(!!(x >> 16))) + 1) & 16);
  count = count + (((~(!!(x >> 8))) + 1) & 8);//If there is a one in the next 8 bits push 8 to the right and add 8 to count , else do nothing
  x = x >> (((~(!!(x >> 8))) + 1) & 8);
  count = count + (((~( !!(x >> 4))) + 1) & 4); //If there is a one in the next 4 bits push 4 to the right and add 4 to count, else do nothing
  x = x >> (((~( !!(x >> 4))) + 1) & 4);
  count = count + (((~( !!(x >> 2))) + 1) & 2);//If there is a one in the next 2 bits push 4 to the right and add 2 to count, else do nothing
  x = x >> (((~( !!(x >> 2))) + 1) & 2);
  count = count + (((~( !!(x >> 1))) + 1) & 1); //If there is a one in the next 1 bits push 1 to the right and add 1 to count, else do nothing
  x = x >> (((~( !!(x >> 1))) + 1) & 1);
 return count; 
}
