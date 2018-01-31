// *
// Fill in the return value for the following procedure, which tests whether its
// first argument is less than or equal to its second. Assume the function f2u
// returns an unsigned 32-bit number having the same bit representation as its
// floating-point argument. You can assume that neither argument is NaN. The two
// flavors of zero, +0 and -0, are considered equal.
//
// int float_le(float x, float y) {
//     unsigned ux = f2u(x);
//     unsigned uy = f2u(y);
//     /* Get the sign bits */
//     unsigned sx = ux >> 31;
//     unsigned sy = uy >> 31;
//
//     /* Give an expression using only ux, uy, sx, and sy */
//     return           ;
// }

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    /* Give an expression using only ux, uy, sx, and sy */
    return ux << 1 == uy << 1       // ux == uy == 0
        || sx && !sy                // x < 0 && y >= 0
        || !sx && !sy && ux <= uy   // x >= 0 && y >= 0
        || sx && sy && ux >= uy;
}
