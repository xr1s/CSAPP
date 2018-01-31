// ****
// Following the bit-level floating-point coding rules, implement the function
// with the following prototype:
//
// /*
//  * Compute (int) f.
//  * If conversion causes overflow or f is NaN, return 0x80000000
//  */
// int float_f2i(float_bits f);
//
//     For floating-point number f, this function computes (int) f. Your
// function should should round toward zero. If f cannot be represented as an
// integer (e.g., it is out of range, or it is NaN), then the function should
// return 0x80000000.
//     Test your function by evaluating it for all 2^32 values of argument f and
// comparing the result to what would be obtained using your machine's floating-
// point operations.

typedef unsigned float_bits;

int float_f2i(float_bits f) {
    unsigned sign = f >> 31 & 0x00000001;
    unsigned expo = f >> 23 & 0x000000ff;
    unsigned frac = f >> 00 & 0x007fffff;

    // Overflow or not a number or infinity or exactly 0x80000000.
    if (expo > 0x9d) return 0x80000000;
    // Underflow or exactly 0.
    if (expo < 0x7f) return 0x00000000;

    // The implied leading 1.
    int result = 1 << expo - 0x7f;
    if (expo > 0x96) {
        result |= frac << expo - 0x96;
    } else {
        result |= frac >> 0x96 - expo;
    }
    if (sign) result = -result;
    return result;
}
