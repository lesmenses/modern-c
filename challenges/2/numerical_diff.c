/* Numerical differentiation using finite differences. */
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#define EPSILON     (1E-8f)
#define DELTA       (1E-5f)

double numerical_diff(double function(double), double x) {
    return (function(x+EPSILON/2.0) - function(x-EPSILON/2.0)) / EPSILON;
}

double approx_equal(double x, double y) {
    return fabs(x-y) < DELTA;
}


int main(void) {
    assert(approx_equal(numerical_diff(cos, 0), -sin(0)));
    assert(approx_equal(numerical_diff(cos, 1), -sin(1)));
    assert(approx_equal(numerical_diff(cos, 2), -sin(2)));

    assert(approx_equal(numerical_diff(sin, 0), cos(0)));
    assert(approx_equal(numerical_diff(sin, 1), cos(1)));
    assert(approx_equal(numerical_diff(sin, 2), cos(2)));

    return EXIT_SUCCESS;
}