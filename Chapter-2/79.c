// **
// Write code for a function mul3div4 that, for integer argument x, computes 3 *
// x/4 but follows the bit-level integer coding rules (page 128). Your code
// should replicate the fact that the computation 3*x can cause overflow.

int mul3div4(int x) {
    int w = sizeof(int) << 3;
    x = (x << 1) + x;
    int bias = 3 & x >> w - 1;
    return x + bias >> 2;
}
