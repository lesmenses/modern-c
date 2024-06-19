#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

double my_strtod(char const * string) {
    double value = 0;
    size_t i = 0;
    signed negative = 1;
    while(string[i] != '.') {
        if(string[i] == '-') {
            negative = -1;
            ++i;
            continue;
        }
        if(string[i] == '\0') return negative * value;
        value = (value * 10) + (string[i] - '0');
        ++i;
    }
    // We are at a period here.
    ++i;
    double multiplier = 0.1;
    while(string[i] != '\0') {
        value += multiplier * (string[i] - '0');
        multiplier /= 10;
        ++i;
    }

    return negative * value;
}

#define EPSILON     (1E-5)
bool approx_equal(double x, double y) {
    return fabs(x-y) < EPSILON;
}

void test_my_strtod(void) {
    printf("Testing strtod.\n");
    assert(approx_equal(my_strtod("123.461"), 123.461));
    assert(approx_equal(my_strtod("-123.461"), -123.461));
    assert(approx_equal(my_strtod("123"), 123));
    assert(approx_equal(my_strtod("0.45"), 0.45));
    assert(approx_equal(my_strtod("-0.45"), -0.45));
}



int main(int argc, char* argv[argc + 1]) {
    test_my_strtod();
    return EXIT_SUCCESS;
}
