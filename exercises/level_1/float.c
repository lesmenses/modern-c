#include <stdio.h>
#include <stdlib.h>
#define LARGE_VALUE (100000.0)

int main(void) {
    printf("1.0E-13 + 1.0E-13=%.15f\n", 1.0E-13 + 1.0E-13);
    printf("(1.0E-13 + (1.0E-13 + large)) - large=%.15f\n", (1.0E-13 + (1.0E-13 + LARGE_VALUE)) - LARGE_VALUE);

    return EXIT_SUCCESS;
}