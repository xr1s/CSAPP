// **
// You are given the task of writing a procedure int_size_is_32() that yields 1
// when run on a machine for which an int is 32 bits, and yields 0 otherwise.
// You are not allowed to use the sizeof operator. Here is a first attempt:
//
//  1    /* The following code does not run properly on some machine */
//  2    int bad_int_size_is_32() {
//  3        /* Set most significant bit (msb) of 32-bit machine */
//  4        int set_msb = 1 << 31;
//  5        /* Shift past msb of 32-bit word */
//  6        int beyond_msb = 1 << 32;
//  7
//  8        /* set_msb is nonzero when word size >= 32
//  9           beyond_msb is zero when word size <= 32  */
// 10        return set_msb && !beyond_msb;
// 11    }
//
//     When compiled and run on a 32-bit SUN SPARC, however, this procedure
// returns 0. The following compiler message gives us an indication of the
// problem:
//
// warning: left shift count >= width of type
// 
//  A. In what way does our code fail to comply with the C standard?
//  B. Modify the code to run properly on any machine for which data type int is
//     at least 32 bits.
//  C. Modify the code to run properly on any machine for which data type int is
//     at least 16 bits.


int int_size_is_32() {
    // answer to A: The behaviour of signed overflow is undefined in C/C++.
    // The behaviour of unsigned overflow is well defined in C/C++.
    unsigned set_msb = 1U << 31;
    unsigned beyond_msb = 1U << 16 << 16;
    return set_msb && !beyond_msb;
}
