// **
// Write a function `good_echo` that reads a buf from standard input and write it to standard output. You implementation should work for an input buf of arbitrary length. You may use library function `fgets`, but you must make sure your function works correctly even when the input buf requires more space than you have allocated for your buffer. Your code should also check for error conditions and return when one is encountered. Refer to the definitioins of the standard I/O function for documentation [45,61].

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Never use readline for reading binary files
char *readline(FILE *fin) {
    size_t cap = 16, len = 0;
    char *buf = calloc(cap, sizeof *buf);
    fgets(buf, cap, fin);
    if (*buf == '\0') {
        free(buf);
        return NULL;
    }
    while (buf[cap - 2] != '\0') {
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

void better_echo() {
    char *line = readline(stdin);
    if (line != NULL)
        fputs(line, stdout);
    free(line);
}

void good_echo() {
#define CAP (16)
    char line[CAP + 1];
    while (fgets(line, sizeof line, stdin)) {
        size_t len = strlen(line);
        fputs(line, stdout);
        if (len != CAP) break;
    }
#undef CAP
}

int main() {
    notbad_echo();
}
