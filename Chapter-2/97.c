// ****
// Following the bit-level floating-point coding rules, implement the function
// with the following prototype:
//
// /* Compute (float) i */
// float_bits float_i2f(int i);
//
//     For argument i, this function computes the bit-level representation of
// (float) i.
//     Test your function by evaluating it for all 2^32 values of argument f and
// comparing the result to what would be obtained using your machine's floating-
// point operations.

typedef unsigned float_bits;

void show_float(unsigned);

float_bits float_i2f(int i) {
    if (!i) return 0x00000000;

    unsigned sign = i >> 31 & 1;
    unsigned frac = i >= 0 ? i : -i;

    // The offset of leftmost 1 in frac.
    // Sorry for function call.
    // But this makes full use of clz assembly instruction.
    unsigned expo = 0x9e -
#if defined(__GNUC__)
        __builtin_clz(frac);
#elif defined(_MSC_VER)
        __lzcnt(frac);
#endif

    // Remove heading one.
    frac &= ~(1u << expo - 0x7f);

    if (expo > 0x96) {
        unsigned trunc = ~0U >> 0xb6 - expo;
        unsigned half = trunc ^ trunc >> 1;
        trunc &= frac;
        int round = trunc > half;
        round |= trunc == half && frac >> expo - 0x96 & 1;
        frac >>= expo - 0x96;
        frac += round;
        if (frac == 0x800000) {
            frac = 0; ++expo;
        }
    } else frac <<= 0x96 - expo;
    return sign << 31 | expo << 23 | frac;
}
