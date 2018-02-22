// **
// Use execve to write a program called myls whose behavior is identical to the
// /bin/ls program. Your program should accept the same command-line arguments, 
// interpret the identical environment variables, and produce the identical
// output.
//     The ls program gets the width of the screen from the COLUMNS environment
// variable. If COLUMNS is unset, then ls assumes that the screen is 80 columns
// wide. Thus, you can check your handling of the environment variables by
// setting the COLUMNS environment to something less than 80:
//
// linux> setenv COLUMNS 40
// linux> ./myls
//   .
//   .  // Output is 40 columns wide
//   .
// linux> unsetenv COLUMNS
// linux> ./myls
//   .
//   .  // Output is now 80 columns wide
//   .

#include <unistd.h>

int main(int argc, char **argv, char **envp) {
    execve("/bin/ls", argv, envp);
}
