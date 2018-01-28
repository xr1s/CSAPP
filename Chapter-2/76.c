// *
// The library function calloc has the following declaration:
//
//  void *calloc(size_t nmemb, size_t size);
//
// According to the library documentation, "The calloc function allocates memory
// for an array of nmemb elements of size bytes eacch. The memory is set to
// zero. If nmemb or size is zero, then calloc returns NULL."
//     Write an implementation of calloc that performs the allocation by a call
// to malloc and sets the memory to zero via memset. Your code should not have
// any vulnerabilities due to arithmetic overflow, and it should work correctly
// regardless of the number of bits used to represent data of type size_t.
//     As a reference, functions malloc and memset have the following
// declarations:
//
// void *malloc(size_t size);
// void *memset(void *s, int c, size_t n);

void *calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    if (total == 0) return NULL;
    void *ptr = malloc(total);
    memset(ptr, 0x00, total);
    return ptr;
}
