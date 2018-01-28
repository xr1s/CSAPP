// **
// 
// Write C expressions that evaluate to 1 when the following conditions are true
// and to 0 when they are false. Assume x is of type int.
//
// A. Any bit of x equals 1.
// B. Any bit of x equals 0.
// C. Any bit in the least significant byte of x equals 1.
// D. Any bit in the most significant byte of x equals 0.
//
// Your code should follow the bit-level integer coding rules (page 128), with
// the addition restriction that you may not use equality (==) or inequality
// (!=) tests.

int A(int x) {
    return !~x;
}

int B(int x) {
    return !x;
}

int C(int x) {
    return !(x & 0xffU ^ 0xffU);
}

int D(int x) {
    int offset = sizeof(int) - 1 << 3;
    unsigned mask = 0xffU << offset;
    return !(x & mask);
}
