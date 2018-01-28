// **
// Write code for the function with the following prototype:
//
// /*
//  * Return 1 when x can be represented as an n-bit, 2's-complement
//  * number; 0 otherwise
//  * Assume 1 <= n <= w
//  */
//  int fits_bits(int x, int n);
//
//      Your function should follow the bit-level integer coding rules (page
//  128).

#include <limits.h>

int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;
    unsigned mask = INT_MIN  >> w - n;
    unsigned sign = x >> w - 1 & mask;
    return x == (x & ~mask | sign);
}
