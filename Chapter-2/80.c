// ***
// Write code for a function threefourths that, for integer argument x, computes
// the value of 3/4*x, rounded towards zero. It should not overflow. Your
// function should follow the bit-level integer coding rules (page 128).

int threefourths(int x) {
    int w = sizeof(int) << 3;
    int bias = x >> w - 1 & 3;
    int h = x + bias >> 2;
    int t = x - (h << 2);
    h = (h << 1) + h;
    t = (t << 1) + t;
    t = t + bias >> 2;
    return h + t;
}
