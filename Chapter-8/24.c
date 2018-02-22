#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int status;
    pid_t pid;

    for (int i = 0; i < 2; ++i)
        if ((pid = fork()) == -1) {
            fprintf(stderr, "Fork error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        } else if (pid == 0) *(int *)main = 0;

    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "child %d terminated by signal %d: ",
                    pid, WTERMSIG(status));
            psignal(WTERMSIG(status), NULL);
        } else {
            fprintf(stderr, "child %d terminated abnormally\n", pid);
        }
    }

    if (errno != ECHILD) {
        fprintf(stderr, "waitpid error: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
