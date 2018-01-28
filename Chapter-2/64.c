// *
// Write code to implement the following function:
//
// /* Return 1 when any odd bit of x equals 1, 0 otherwise.
//    Assume w=32 */
// int any_odd_one(unsigend x);
// 
//     Your function should follow the bit-level integer coding rules (page 128)
// except that you may assume that data type int has w = 32 bits.

int any_odd_one() {
    return !!(x & 0xaaaaaaaa);
}
