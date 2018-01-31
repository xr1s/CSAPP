// ***
// Following the bit-level float-point coding rules, implement the function with
// the following prototype:
//
// /* Compute 2*f.  If f is NaN, then return f. */
// float_bits float_twice(float_bits f);
//
//     For floating-point number f, this function computes 2.0 * f, If f is NaN,
// your function should simply return f.
//     Test your function by evaluating it for all 2^32 values of argument f and
// comparing the result to what would be obtained using your machine's floating-
// point operations.

typedef unsigned float_bits;

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31 & 0x00000001;
    unsigned expo = f >> 23 & 0x000000ff;
    unsigned frac = f >> 00 & 0x007fffff;
    switch (expo) {
      case 0xff:  // If f is NaN or infinity
        break;
      case 0xfe:  // If f is almost infinity
        frac = 0;
        // fallthrough deliberately
      default:    // If f is normalized
        ++expo;
        break;
      case 0x00:  // If f is denormalized
        if (frac >> 22) {  // f should be normalized
            expo = 1;
            frac <<= 10;
            frac >>= 9;
        } else frac <<= 1;
        break;
    }
    return sign << 31 | expo << 23 | frac;
}
