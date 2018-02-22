// ***
// Write a version of the fgets function, called tfgets, that times out after 5
// seconds. The tfgets function accepts the same inputs as fgets. If the user
// doesn't type an input line within 5 seconds, tfgets returns NULL. Otherwise a
// pointer to the input line.

#include <unistd.h>
#include <signal.h>

#include <setjmp.h>
#include <stdio.h>

static sigjmp_buf tfgets_jmpbuf;

void tfgets_timeout(int sig) {
    siglongjmp(tfgets_jmpbuf, 1);
}

char *tfgets(char *s, int size, FILE *stream) {
    static struct sigaction oact, act = {
        .sa_handler = tfgets_timeout,
        .sa_flags = SA_RESTART,
    };
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGALRM, &act, &oact) == -1)
        return NULL;
    char *result = NULL;

    alarm(5);

    if (sigsetjmp(tfgets_jmpbuf, 1) == 0) {
        result = fgets(s, size, stream);
        alarm(0);  // cancel previous alarm
    }

    sigaction(SIGALRM, &oact, NULL);
    return result;
}
