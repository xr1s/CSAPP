// *
// Modify the cpfile program in Figure 10.5 it uses the RIO functions to copy
// standard input to standard output, MAXBUF bytes at a time.

#include "csapp.h"

ssize_t cpfile(int srcfd, int dstfd) {
  ssize_t total = 0, n;
  char buf[MAXBUF];
  do {
    n = rio_readn(srcfd, buf, MAXBUF);
    total += n;
    if (n == -1) {
      return -1;
    }
    rio_writen(dstfd, buf, n);
  } while (n == MAXBUF);
  return total;
}

int main() {
  cpfile(STDIN_FILENO, STDOUT_FILENO);
}
