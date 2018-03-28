#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
    int fd1, fd2;

    fd1 = open("foo.txt", O_RDONLY, 0);
    fd2 = open("bar.txt", O_RDONLY, 0);
    close(fd2);
    fd2 = open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
}
