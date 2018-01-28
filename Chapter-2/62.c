// ***
// Write a function int_shifts_are_arithmetic() that yields 1 when run on a
// machine that uses arithmetic right shifts for data type int and yields 0
// otherwise. Your code should work on a machine with any word size. Test your
// code on several machines.

int int_shifts_are_arithmetic() {
#if -1 >> 1 == -1
    return 1;
#else
    return 0;
#endif
}
