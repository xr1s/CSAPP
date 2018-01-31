// *
// You have been assigned the task of writing a C function to compute a floating
// -point representation of 2^x. You decide that the best way to do this is to
// directly construct the IEEE single-precision representation of the result.
// When x is too small, your routine will return 0.0. When x is too large, it
// will return +∞. Fill in the blank portions of the code that follows to
// compute the correct result. Assume the function u2f returns a floating-point
// value having an identical bit representation as its unsigned argument.
//
// float fpwr2(int x)
// {
//     /* Result exponent and fraction */
//     unsigned exp, frac;
//     unsigned u;
//
//     if (x < _________) {
//         /* Too small.  Return 0.0 */
//         exp =  _________;
//         frac = _________;
//     } else if (x < _________) {
//         /* Denormalized result */
//         exp =  _________;
//         frac = _________;
//     } else if (x < _________) {
//         /* Normalized result. */
//         exp =  _________;
//         frac = _________;
//     } else {
//         /* Too big.   Return +oo */
//         exp =  _________;
//         frac = _________;
//     }
//
//     /* Pack exp and frac into 32 bits */
//     u = exp << 23 | frac;
//     /* Return as float */
//     return u2f(u);
// }


float fpwr2(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        /* Too small.  Return 0.0 */
        exp =  0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result */
        exp =  0;
        frac = 1 << x + 149;
    } else if (x < 128) {
        /* Normalized result. */
        exp =  x + 127;
        frac = 0;
    } else {
        /* Too big.   Return +oo */
        exp =  255;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
