#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

size_t fib(size_t n) {
    if(n < 3) return n;
    return fib(n-1) + fib(n-2);
}

int main(int argc, char* argv[argc + 1]) {
    if(argc != 2) {
        printf("Need one arg.");
        return EXIT_FAILURE;
    }
    printf("%lu is n=%s Fibonacci number.\n", fib(strtoul(argv[1], 0, 10)),
        argv[1]);

    return EXIT_SUCCESS;
}