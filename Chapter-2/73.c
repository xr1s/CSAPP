// **
// Write code for a function with the following prototype:
//
// /* Addition that saturates to TMin or TMax */
// int saturating_add(int x, int y);
//
//     Instead of overflowing the way normal two's-complement addtion does,
// saturating addition returns TMax when there would be positive overflow, and
// TMin when there would be negative overflow. Saturating arithmetic is commonly
// used in programs that perform digital signal processing.
//     Your function should follow the bit-level integer coding rules (page 128)

#include <limits.h>

int saturating_add(int x, int y) {
#define UX ((unsigned) x)
#define UY ((unsigned) y)
    int w = sizeof(int) << 3;
    unsigned sign_of_x = UX >> w - 1, sign_of_y = UY >> w - 1;
    unsigned sum = UX + UY, sign_of_sum = sum >> w - 1;
#define SX sign_of_x
#define SY sign_of_y
#define SS sign_of_sum
    // If there is no overflow, value of overflow will be 0U;
    // if there is overflow, value of overflow will be ~0U.
    // positive_overflow and negative_overflow are the same as overflow.
    unsigned overflow = -(SX ^ SS && SY ^ SS);
    unsigned positive_overflow = -(!SX && !SY && SS);
    unsigned negative_overflow = -(SX && SY && !SS);
#define O overflow
#define PO positive_overflow
#define NO negative_overflow
    return ~O & sum | PO & INT_MAX | NO & INT_MIN;
#undef O
#undef NO
#undef PO
#undef SS
#undef SY
#undef SX
#undef UX
#undef UY
}
