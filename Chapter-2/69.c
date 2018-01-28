// ***
// Write code for a function with the following prototype:
//
// /*
//  * Do rotating left shift.  Assum 0 <= n < w
//  * Examples when x = 0x12345678 and w = 32:
//  *    n=4 -> 0x23456781, n=20 -> 0x67812345
//  */
// unsigned rotate_left(unsigned x, int n);
//
//     Your function should follow the bit-level integer coding rules (page 128)
// Be careful of the case n = 0.

unsigned rotate_left(unsigned x, int n) {
    return x << n | x >> (sizeof(unsigned) << 3) - n - 1 >> 1;
}
