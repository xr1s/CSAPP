// *
// Write procedure show_short, show_long, and show_double that print the byte
// representation of C objects of type short, long, and double, respectively.
// Try these out on several machines.

#include <stdio.h>

typedef unsigned char byte;

void show_bytes(byte *start, size_t len) {
    for (size_t i = 0; i != len; ++i)
        printf("%.2x%c", start[i], i + 1 != len ? ' ' : '\n');
}

void show_long(long x) {
    show_bytes((byte *)&x, sizeof(long));
}

void show_double(double x) {
    show_bytes((byte *)&x, sizeof(double));
}

void show_pointer(void *x) {
    show_bytes((byte *)&x, sizeof(void *));
}
