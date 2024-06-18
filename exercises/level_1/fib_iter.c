#include <stdlib.h>
#include <stdio.h>

size_t fib2_iter(size_t n) {
    size_t buffer[2] = {1, 1};
    for(size_t i = 2; i < n; ++i) {
        size_t value = buffer[0] + buffer[1];
        buffer[1] = buffer[0];
        buffer[0] = value;
    }

    return buffer[0];
}

int main(int argc, char* argv[argc + 1]) {
    if(argc != 2) {
        printf("Need one arg.");
        return EXIT_FAILURE;
    }
    printf("%lu is n=%s Fibonacci number.\n", fib2_iter(strtoul(argv[1], 0, 10)),
        argv[1]);

    return EXIT_SUCCESS;
}