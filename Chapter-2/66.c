// ***
// Write code to implement the following function:
//
// /*
//  * Generate mask indicating leftmost 1 in x.  Assume w=32.
//  * For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
//  * If x = 0, then return 0.
//  */
//  int leftmost_one(unsigned x);
//
//     Your function should follow the bit-level integer coding rules (page 128)
// except that you may assume that data type int has w = 32 bits.
//     Your code should contain a total of at most 15 arithmetic, bitwise, and
// logical operations.
//     Hint: First tranform x into a bit vector of the form [0...011...1].

int leftmost_one(unsigned x) {
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x - (x >> 1);
}
