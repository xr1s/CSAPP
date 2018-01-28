// **
// Write code for a function with the following prototype:
// /*
//  * Mask with least signficant n bits set to 1
//  * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
//  * Assume 1 <= n <= w
//  */
//  int lower_one_mask(int n);
//
//    Your function should follow the bit-level integer coding rules (page 128).
// Be careful of the case n = w.

int lower_one_mask(int n) {
    return ~0U >> (sizeof(int) << 3) - n;
}
