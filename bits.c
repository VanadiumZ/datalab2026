/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !((x >> 31) ^ (y >> 31)) && !(!x ^ !y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;
    int shift;

    shift = (v > 0xFFFF) << 4;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0xFF) << 3;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0xF) << 2;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0x3) << 1;
    result = result | shift;
    v = v >> shift;

    shift = (v > 0x1);
    result = result | shift;

    return result;
}
// -- A version with less ops --
// int logtwo(int v) {
//     int result = (v > 0xFFFF) << 4;
//     int shift;
//     v = v >> result;
//     shift = (v > 0xFF) << 3;
//     result = result | shift;
//     v = v >> shift;
//     shift = (v > 0xF) << 2;
//     result = result | shift;
//     v = v >> shift;
//     shift = (v > 3) << 1;
//     result = result | shift;
//     v = v >> shift;
//     return result | (v >> 1);
// }

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n << 3;
    int mshift = m << 3;
    int a = (x >> nshift) & 0xFF;
    int b = (x >> mshift) & 0xFF;
    int diff = a ^ b;
    x = x ^ (diff << nshift);
    x = x ^ (diff << mshift);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
    return v;
}
// -- Another solution with a while loop --
// unsigned reverse(unsigned v) {
//     unsigned result = 0;
//     int count = 32;
//     while (count) {
//         result = (result << 1) | (v & 1);
//         v = v >> 1;
//         count = count - 1;
//     }
//     return result;
// }

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0;
    int shift;

    shift = !~(x >> 16) << 4;
    count += shift;
    x = x << shift;

    shift = !~(x >> 24) << 3;
    count += shift;
    x = x << shift;

    shift = !~(x >> 28) << 2;
    count += shift;
    x = x << shift;

    shift = !~(x >> 30) << 1;
    count += shift;
    x = x << shift;
    
    shift = !~(x >> 31) & 1;
    count += shift;
    x = x << shift;

    count += !~(x >> 31);

    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000u;
    unsigned value = x;
    unsigned exponent = 158;
    unsigned fraction;
    unsigned remainder;
    if (!x) {
        return 0;
    }
    if (sign) {
        value = ~value + 1;
    }
    while (!(value & 0x80000000u)) {
        value = value << 1;
        exponent = exponent - 1;
    }
    fraction = (value >> 8) & 0x7FFFFF;
    remainder = value & 0xFF;
    if ((remainder > 0x80) | ((remainder == 0x80) & (fraction & 1))) {
        fraction = fraction + 1;
    }
    return sign | ((exponent << 23) + fraction);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF)
        return uf;

    if (exp == 0)
        return sign | (frac << 1);

    if (exp == 0xFE)
        return sign | 0x7F800000;

    return sign | ((exp + 1) << 23) | frac;
}
// unsigned floatScale2(unsigned uf) {
//     unsigned sign = uf & 0x80000000u;
//     unsigned exponent = uf & 0x7F800000;
//     unsigned fraction = uf & 0x7FFFFF;
//     if (exponent == 0x7F800000) {
//         return uf;
//     }
//     if (!exponent) {
//         return sign | (fraction << 1);
//     }
//     exponent = exponent + 0x800000;
//     if (exponent == 0x7F800000) {
//         return sign | exponent;
//     }
//     return sign | exponent | fraction;
// }

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exponent = (uf2 >> 20) & 0x7FF;
    int value;
    unsigned fraction = (uf2 & 0xFFFFF) | 0x100000;
    exponent = exponent - 1023;
    if (exponent < 0) {
        return 0;
    }
    if (exponent > 30) {
        return ~0x7FFFFFFF;
    }
    if (exponent > 20) {
        value = (fraction << (exponent - 20)) | (uf1 >> (52 - exponent));
    } else {
        value = fraction >> (20 - exponent);
    }
    if (uf2 >> 31) {
        return -value;
    }
    return value;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }
    if (x < -126) {
        return 1u << (x + 149);
    }
    if (x > 127) {
        return 0x7F800000;
    }
    return (x + 127) << 23;
}
