// ***
// Following the bit-level floating-point coding rules, implement the function
// with the following prototype:
//
// /* Compute 0.5*f.  If f is NaN, then return f. */
// float_bits float_half(float_bits f);
//
//     For floating-point number f, this function computes 0.5 * f. If if is NaN
// your function should simply return f.
//     Test your function by evaluating it for all 2^32 values of argument f and
// comparing the result to what would be obtained using your machine's floating
// -point operations.

typedef unsigned float_bits;

float_bits float_half(float_bits f) {
    unsigned sign = f >> 31 & 0x00000001;
    unsigned expo = f >> 23 & 0x000000ff;
    unsigned frac = f >> 00 & 0x007fffff;
    unsigned round = (frac & 3) == 3;
    switch (expo) {
      case 0xff:  // If f is NaN or infinity
        break;
      case 0x01:  // If f is almost denormalized
        if (frac != 0x7fffff) {
            frac >>= 1;
            frac += 0x400000;
            frac += round;
            --expo;
        } else frac = 0;
        break;
      case 0x00:  // If f is denormalized
        frac >>= 1;
        frac += round;
        break;
      default:    // If f is normalized
        --expo;
        break;
    }
    return sign << 31 | expo << 23 | frac;
}
