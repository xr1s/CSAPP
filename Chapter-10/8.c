// **
// Write a version of the statcheck program in Figure 10.10 called fstatcheck
// that takes a descriptor number on the command line rather than a filename.

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mode_t fstatcheck(int fd) {
  struct stat st;
  int err = fstat(fd, &st);
  if (err == -1) 
    return ~(mode_t)0;
  return st.st_mode;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "%s: Please specify the file descriptor.\n", argv[0]);
    return EXIT_FAILURE;
  }

  int fd = atoi(argv[1]);
  mode_t mode = fstatcheck(fd);

  if (mode == ~(mode_t)0) {
    fprintf(stderr, "fstat: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  const char *type, *readable;

  switch (mode & S_IFMT) {
   case S_IFSOCK: type = "socket"; break;
   case S_IFLNK:  type = "symbolic link"; break;
   case S_IFREG:  type = "regular file"; break;
   case S_IFBLK:  type = "block device"; break;
   case S_IFDIR:  type = "directory"; break;
   case S_IFCHR:  type = "character device"; break;
   case S_IFIFO:  type = "FIFO"; break;
  }

  char ur = mode & S_IRUSR ? 'r' : '-';
  char uw = mode & S_IWUSR ? 'w' : '-';
  char ux = mode & S_IXUSR ? 'x' : '-';
  char gr = mode & S_IRGRP ? 'r' : '-';
  char gw = mode & S_IWGRP ? 'w' : '-';
  char gx = mode & S_IXGRP ? 'x' : '-';
  char or = mode & S_IROTH ? 'r' : '-';
  char ow = mode & S_IWOTH ? 'w' : '-';
  char ox = mode & S_IXOTH ? 'x' : '-';

  printf("file type: %s\nprivilege: %c%c%c%c%c%c%c%c%c\n", type, 
         ur, uw, ux, gr, gw, gx, or, ow, ox);

}
