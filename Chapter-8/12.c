// *
// How many "hello" output lines does this program print?

#include "csapp.h"

void doit()
{
    Fork();
    Fork();
    printf("hello\n");
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}

// hello
// hello
// hello
// hello
// hello
// hello
// hello
// hello

