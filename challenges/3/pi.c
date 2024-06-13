/* 
    Calculating first N digits of Pi using power series expansion
    https://cs.uwaterloo.ca/~alopez-o/math-faq/mathtext/node12.html

    Note program starts to fail after around 16 digits due to overflow
    when raising 10^digits in is_n_digits_matching.
*/

#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool is_n_digits_matching(size_t digits, double estimate) {
    return (unsigned long long)(estimate * pow(10, digits-1)) == (unsigned long long)(M_PI * pow(10, digits-1));
}

#define MAX_ITERATIONS  (100)


double estimate_pi(size_t digits) {
    double estimate = 0;
    double atan_1_5 = 0;
    double atan_1_239 = 0;
    size_t iteration = 0;
    while(1) {
        size_t term = iteration * 2 + 1;
        double add_1_5 = pow((1.0/5), term) / term;
        double add_1_239 = pow((1.0 / 239), term) / term;  
        if(iteration % 2 == 0) {
            atan_1_5 += add_1_5;
            atan_1_239 += add_1_239;
        } else {
            atan_1_5 -= add_1_5;
            atan_1_239 -= add_1_239;
        }

        estimate = 16*atan_1_5 - 4*atan_1_239;
        if(is_n_digits_matching(digits, estimate)) {
            break;
        }
        printf("Intermediate estimate: %.18f\n", estimate);
        ++iteration;    
    }

    return estimate;
}

int main(int argc, char* argv[argc + 1]) {
    if(argc != 2) {
        printf("Need one input.\n");
        return EXIT_FAILURE;
    }
    size_t digits = strtoul(argv[1], (void*)0, 10);
    if(!digits) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("Pi estimate: %.20f\n", estimate_pi(digits));
    printf("Pi         : %.20f\n", M_PI);
}