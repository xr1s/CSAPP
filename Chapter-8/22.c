// ***
// Write your own version of the Unix system function
//
// int mysystem(char *command);
//
// The mysystem function executes command by invoking /bin/sh -c command, and
// then returns after command has completed. If command exits normally (by
// calling the exit function or executing a return statement), then my system
// returns the command exit status. For example, if command terminates by
// calling exit(8), then mysystem returns the value 8. Otherwise, if command
// terminates abnormally, then mysystem returns the status returned by the
// shell.

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int mysystem(const char *command) {
    extern char **environ;
    char *argv[] = {
        "sh", "-c", (char *)command, NULL,
    };
    pid_t pid = fork();
    if (pid == -1) return -1;
    if (pid != 0) {
        int stat;
        if (waitpid(pid, &stat, 0) == -1) return -1;
        if (WIFEXITED(stat))
            return WEXITSTATUS(stat);
        return 0;
    } else execve("/bin/sh", argv, environ);
}
