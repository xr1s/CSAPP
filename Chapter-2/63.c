// ***
// Fill in code for the following C funtions. Funtion sr performs a logic right
// shift using an arithmetic right shift (given by value xsra), followed by
// other operations not included right shifts or division. Function sra performs
// an arithmetic operations not including right shifts or division. You may use
// the computation 8*sizeof(int) to determine w, the number of bits in data type
// int. The shift amout k can range from 0 to w - 1.
//
// unsigned srl(unsigned x, int k) {
//     /* Perform shift arithmetically */
//     unsigned xsra = (int) x >> k;
// .
// .
// .
// .
// .
// .
// }
//
// int sra(int x, int k) {
//     /* Perform shift logically */
//     int xsrl = (unsigned) x >> k;
// .
// .
// .
// .
// .
// .
// }

unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    int w = sizeof(int) << 3;
    unsigned neg = x >> w - 1 & 1U;
    unsigned mask = ~(-neg << w - k);
    return xsra & mask;
}

int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    unsigned neg = x >> w - 1 & 1U;
    unsigned mask = -neg << w - k;
    return xsrl | mask;
}
