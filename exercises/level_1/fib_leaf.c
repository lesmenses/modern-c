#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

size_t fib_leaf(size_t n) {
    if(n < 3) return 1;
    return fib_leaf(n-1) + fib_leaf(n-2);
}

int main(int argc, char* argv[argc + 1]) {
    if(argc != 2) {
        printf("Need one arg.");
        return EXIT_FAILURE;
    }
    printf("%lu leaf calls for n=%s\n", fib_leaf(strtoul(argv[1], 0, 10)),
        argv[1]);

    return EXIT_SUCCESS;
}