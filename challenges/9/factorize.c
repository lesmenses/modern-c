#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_FACTORS     (100UL)

size_t get_smallest_factor(size_t value) {
    for(size_t i = 2; i <= value/2; ++i) {
        if(value % i == 0) {
            return i;
        }
    }

    return value;
}

size_t factorize_recursive(size_t value, size_t index, size_t n, size_t buffer[n]) {
    assert(index);
    size_t smallest_factor = get_smallest_factor(value);

    if(smallest_factor != buffer[index-1]) {
        buffer[index] = smallest_factor;
        ++index;
    }
    if(smallest_factor == value) {
        return index;
    }

    return factorize_recursive(value/smallest_factor, index, n, buffer);
}

size_t factorize(size_t value, size_t buffer[static MAX_FACTORS]) {
    assert(value);
    buffer[0] = 1;
    return factorize_recursive(value, 1, MAX_FACTORS, buffer);
}

void factorize_print(size_t value) {
    size_t buffer[MAX_FACTORS] = {0};
    size_t number_of_factors = factorize(value, buffer);

    printf("%lu: ", value);
    for(size_t i = 0; i < number_of_factors; ++i) {
        printf("%lu ", buffer[i]);
    }
    printf("\n");
}

void print_array(size_t n, size_t x[static n]) {
    printf("[ ");
    for(size_t i = 0; i < n; ++i) {
        printf("%lu ", x[i]);
    }
    printf("]\n");

}

bool is_arrays_equal(size_t n, size_t x[static n], size_t y[static n]) {
    for(size_t i = 0; i < n; ++i) {
        if(x[i] == y[i]) continue;
        printf("Array check failed at %lu\n", i);
        printf("x=");
        print_array(n, x);
        printf("y=");
        print_array(n, y);
        return false;
    }

    return true;
}

void test_factorize(void) {
    printf("Testing factorize.\n");
    size_t buffer[MAX_FACTORS] = {0};
    size_t expected[MAX_FACTORS] = {1, 2, 3, 7};
    assert(factorize(42, buffer) == 4);
    assert(is_arrays_equal(4, buffer, expected));
}

int main(int argc, char* argv[argc+1]) {
    test_factorize();
    for(size_t i = 1; i < argc; ++i) {
        factorize_print(strtoul(argv[i], 0, 10));
    }

    return EXIT_SUCCESS;
}