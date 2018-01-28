// **
// Write C expression to generate the bit pattern that follow where a^{k}
// represents k repetitions of symbol a. Assume a w-bit data type. Your code may
// contain references to parameter j and k, representing the values of j and k,
// but not a parameter representing w.
//
//  A. 1^{w-k}0^{k}
//  B. 0^{w-k-j}1^{k}0^{j}

unsigned A(int k) {
    return k == 32 ? 0 : ~0U << k;
}

unsigned B(int j, int k) {
#define W (sizeof(int) << 3)
    return j == 32 || k == 0 ? 0U : ~0U >> j << W - k >> W - k - j;
#undef W
}
