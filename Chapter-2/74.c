// **
// Write a function with the following prototype:
//
// /* Determine wheter arguments can be subtracted without overflow */
// int isub_ok(int x, int y);
//
//     This function should return 1 if the computation x-y does not overflow.

int tsub_ok(int x, int y) {
    int w = sizeof(int) << 3;
    unsigned sx = (unsigned) x >> w - 1, sy = (unsigned) y >> w - 1;
    unsigned sub = (unsigned) x - (unsigned) y, ss = sub >> w - 1;
    return sx ^ sy && sx ^ ss;
}
