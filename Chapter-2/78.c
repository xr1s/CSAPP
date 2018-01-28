// **
// Write code for a function with the following prototype:
//
// /* Divide by power of 2. Assume 0 <= k < w-1 */
// int divide_power2(int x, int k);
//
//     The function should compute x/2^k with correct rounding, and it should
// follow the bit-level integer coding rules (page 128).

#include <stdio.h>

int divide_power2(int x, int k) {
    int w = sizeof(int) << 3;
    int bias = (1 << k) - 1 & x >> w - 1;
    return x + bias >> k;
}
