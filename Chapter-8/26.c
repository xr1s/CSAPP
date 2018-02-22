#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

static pid_t foreground;

char *readline(FILE *fin) {
    size_t cap = 16, len = 0;
    char *buf = calloc(cap, sizeof *buf);
    fgets(buf, cap, fin);
    if (*buf == '\0') {
        free(buf);
        return NULL;
    }
    while (buf[cap - 2] != '\0' && buf[cap - 2] != '\n') {
        len = cap - 1;
        cap = cap * 3 / 2;
        char *alt = realloc(buf, cap);
        if (alt == NULL) {
            free(buf);
            return NULL;
        } else buf = alt;
        fgets(buf + len, cap - len, fin);
    }
    len += strlen(buf + len);
    return buf;
}

void prompt() {
    printf("xsh> ");
}

char *search_path(char *file) {
    static char *path[] = {
        "/usr/local/bin",
        "/usr/local/sbin",
        "/usr/bin",
        "/usr/sbin",
        NULL,
    };
    for (char **p = path; *p; ++p) {
        DIR *d = opendir(*p);
        if (d == NULL) continue;
        struct dirent *n;
        while ((n = readdir(d))) {
            if (strcmp(n->d_name, file) == 0) {
                closedir(d);
                return *p;
            }
        }
        if (closedir(d) == -1)
            fprintf(stderr, "closedir: %s\n", strerror(errno));
    }
    return NULL;
}

int builtin(char **argv) {
    if (strcmp(argv[0], "cd") == 0) {
        if (chdir(argv[1]) == -1)
            fprintf(stderr, "cd: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

char **parse(char *cmd) {
    int argc = 1, prev_space = 1, this_space;

    while (*cmd && isspace(*cmd)) ++cmd;
    if (*cmd == '\0') return NULL;

    for (char *p = cmd; *p; p++) {
        this_space = isspace(*p);
        if (prev_space && !this_space) ++argc;
        prev_space = this_space;
    }

    char **argv = malloc(argc * sizeof(char *));

    argc = 0;
    prev_space = 1;
    for (char *p = cmd; *p; p++) {
        this_space = isspace(*p);
        if (prev_space && !this_space) argv[argc++] = p;
        if (!prev_space && this_space) *p = '\0';
        prev_space = this_space;
    }
    argv[argc++] = NULL;

    return argv;
}

void eval(char *cmd) {

    char **argv = parse(cmd);
    if (argv == NULL)
        return;

    if (builtin(argv))
        return;

    char **end = argv;
    while (*end != NULL) ++end;

    int bg = **--end == '&';
    if (bg) *end = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        return;
    }
    if (pid == 0) {

        char *path = search_path(argv[0]);
        size_t path_len = strlen(path), file_len = strlen(argv[0]);
        char *filepath = malloc(path_len + file_len + 2);
        strcpy(filepath, path);
        filepath[path_len] = '/';
        strcpy(filepath + path_len + 1, argv[0]);

        if (execve(filepath, argv, environ) == -1)
            fprintf(stderr, "execve: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        if (bg) {
            printf("[+] %d\n", pid);
        } else {
            foreground = pid;
            if (waitpid(pid, NULL, 0) == -1)
                if (errno != ECHILD)
                    fprintf(stderr, "waitpid: %s\n", strerror(errno));
            foreground = 0;
        }
    }

    free(argv);

}

void reap(int sig) {
    pid_t pid = wait(NULL);
    if (pid == -1) {
        if (errno != ECHILD)
            fprintf(stderr, "wait: %s\n", strerror(errno));
    } else printf("[-] %d\n", pid);
}

void proxy(int sig) {
    if (foreground) kill(foreground, sig);
    putchar('\n');
    prompt();
    fflush(stdout);
}

int main(int argc, char **argv) {

    char *cmd;

    signal(SIGCHLD, reap);
    signal(SIGINT, proxy);

    while (1) {
        prompt();
        cmd = readline(stdin);
        if (cmd == NULL) break;
        eval(cmd);
        free(cmd);
    }

    puts("\033[1mBye\033[0m");

}
