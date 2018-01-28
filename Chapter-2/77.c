// **
// Suppose we are given the task of generating code to multiply integer variable
// x by variouse different constant factors K. To be efficient, we want to use
// only the operations +, -, and <<. For the following values of K, write C
// expressions to perform the multiplication using at most three operations per
// expression.
//
//   A. K = 17
//   B. K = -7
//   C. K = 60
//   D. K = -112

int A(int x) {
    return (x << 4) + x;
}

int B(int x) {
    return x - (x << 3);
}

int C(int x) {
    return (x << 6) - (x << 2);
}

int D(int x) {
    return (x << 4) - (x << 7);
}
