// *
// How many "hello" output lines does this program print?

#include "csapp.h"

int main()
{
    int i;

    for (i = 0; i < 2; i++)
        Fork();
    printf("hello\n");
    exit(0);
}

// hello
// hello
// hello
// hello
