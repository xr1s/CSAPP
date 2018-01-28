// **
// Write a procedure is_little_endian that will return 1 when compiled and run
// on a little-endian machine, and will return 0 when compiled and run on a big-
// endian machine. This program should return on any machine, regardless of its
// word size.

int is_little_endian() {
    static const int i = 1;
    return *(char *)&i;
}
