/* Numerical differentiation using finite differences. */
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <complex.h>
#include <tgmath.h>
#include <stdio.h>

#define EPSILON     (1E-8)
#define EPSILON_COMPLEX (EPSILON + EPSILON*I)
#define DELTA       (1E-5f)

double complex numerical_diff(double complex function(double complex), double complex x) {
    return (function(x+EPSILON_COMPLEX/2.0) - function(x-EPSILON_COMPLEX/2.0)) / EPSILON_COMPLEX;
}

double approx_equal(double complex x, double complex y) {
    return cabs(x-y) < DELTA;
}


int main(void) {
    assert(approx_equal(numerical_diff(ccos, 0), -csin(0)));
    assert(approx_equal(numerical_diff(ccos, 1), -csin(1)));
    assert(approx_equal(numerical_diff(ccos, 2), -csin(2)));
    assert(approx_equal(numerical_diff(ccos, 0+0.5*I), -csin(0+0.5*I)));
    assert(approx_equal(numerical_diff(ccos, 1-0.5*I), -csin(1-0.5*I)));
    assert(approx_equal(numerical_diff(ccos, 2+0.5*I), -csin(2+0.5*I)));

    assert(approx_equal(numerical_diff(csin, 0-0.5*I), ccos(0-0.5*I)));
    assert(approx_equal(numerical_diff(csin, 1+0.5*I), ccos(1+0.5*I)));
    assert(approx_equal(numerical_diff(csin, 2-0.5*I), ccos(2-0.5*I)));
    assert(approx_equal(numerical_diff(csin, 0+0.5*I), ccos(0+0.5*I)));
    assert(approx_equal(numerical_diff(csin, 1-0.5*I), ccos(1-0.5*I)));
    assert(approx_equal(numerical_diff(csin, 2+0.5*I), ccos(2+0.5*I)));

    printf("Completed complex.\n");

    return EXIT_SUCCESS;
}