// *
// How many hello lines does this program print?

#include "csapp.h"

void doit()
{
    if (Fork() == 0) {
        Fork();
        printf("hello\n");
    }
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
