// **
// Write a C expression that will yield a word consisting of the least
// significant byte of x and the remaining bytes of y. For operands x =
// 0x89ABCDEF and y = 0x76543210, this would give 0x765432EF.

unsigned foo(unsigned x, unsigned y) {
    return x & 0xff | y & ~0U << 8;
}
