// **
// Suppose we number the bytes in a w-bit word from 0 (least significant) to
// w/8 - 1 (most significant). Write code for the following C function, which
// will return an unsigned value in which byte i of argument x has been replaced
// by byte x.
//
// unsigned replace_byte (unsigned x, int i, unsigned char b);
//
//    Here are some examples showing how the function should work:
//
// replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
// replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    int offset = i << 3;
    unsigned mask = ~(0xffU << offset);
    return x & mask | b << offset;
}
