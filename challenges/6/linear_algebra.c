#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON     (1e-5)
bool approx_equal(double x, double y);
void print_matrix(size_t m, size_t n, double x[static m][n]);

double dot_product(size_t length, double vector_1[static length],
    double vector_2[static length]) {
    if (!length) assert(0);

    double product = 0;
    for(size_t i = 0; i < length; ++i) {
        product += vector_1[i] * vector_2[i];
    }

    return product;
}

void cross_product(double vector_1[static 3], double vector_2[static 3], double result[static 3]) {
    result[0] = vector_1[1] * vector_2[2] - vector_1[2] * vector_2[1];
    result[1] = vector_1[2] * vector_2[0] - vector_1[0] * vector_2[2];
    result[2] = vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0];
}

void matrix_vector_product(size_t m, size_t n, double matrix[static m][n],
    double vector[static n], double result[static n]) {
    if(!m) assert(0);
    if(!n) assert(0);
    for(size_t i = 0; i < m; ++i) {
        double product = 0;
        for(size_t j = 0; j < n; ++j) {
            product += matrix[i][j] * vector[j];
        }
        result[i] = product;
    }
}

void swap_rows(size_t m, size_t n, size_t row, double matrix[m][n]) {
    for(size_t i = row+1; i < m; ++i) {
        // Skip if no value at given element.
        if(approx_equal(matrix[i][row], 0.0))
            continue;
        
        for(size_t j = 0; j < n; ++j) {
            double temp = matrix[row][j];
            matrix[row][j] = matrix[i][j];
            matrix[i][j] = temp;
        }
        break;
    }
}

void scale_row(size_t m, size_t n, size_t row, double scale, double matrix[m][n]) {
    for(size_t j = 0; j < n; ++j) {
        matrix[row][j] *= scale;
    }
}

void subtract_row(size_t m, size_t n, size_t row, size_t row_sub, double matrix[m][n]) {
    for(size_t j = 0; j < n; ++j) {
        matrix[row][j] -= matrix[row_sub][j];
    }
}

void gauss_elimination(size_t m, size_t n, double matrix[static m][n]) {
    for(size_t i = 0; i < m; ++i) {
        // Shuffle rows s.t. ith row has a value on the diagonal.
        if(approx_equal(matrix[i][i], 0.0))
            swap_rows(m, n, i, matrix);
        // Perform row operations s.t. there are no leading values.
        for(size_t op_row = 0; op_row < i; ++op_row) {
            scale_row(m, n, i, matrix[op_row][op_row] / matrix[i][op_row], matrix);
            subtract_row(m, n, i, op_row, matrix);
        }
        //TODO: what if this is a redundant row (i.e. becomes zero here.)
        // Scale row s.t. diagonal element has 1.
        scale_row(m, n, i, 1.0 / matrix[i][i], matrix);
    }
}

// Using Newton-Schulz iterative method.
// https://math.stackexchange.com/questions/2298526/computing-inverse-of-a-matrix-when-a-good-starting-guess-is-available
void matrix_transpose(size_t m, double matrix[m][m], double transpose[m][m]) {
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < m; ++j) {
            transpose[i][j] = matrix[j][i];
        }
    }
}
void matrix_copy(size_t m, double matrix[m][m], double result[m][m]) {
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < m; ++j) {
            result[i][j] = matrix[i][j];
        }
    }
}
double row_column_product(size_t m, size_t row, size_t col, double a[m][m], double b[m][m]) {
    double result = 0;
    for(size_t i = 0; i < m; ++i) {
        result += a[row][i] * b[i][col];
    }
    return result;
}
void matrix_multiplication(size_t m, double a[m][m], double b[m][m], double result[m][m]) {
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < m; ++j) {
            result[i][j] = row_column_product(m, i, j, a, b);
        }
    }
}
void matrix_subtraction(size_t m, double a[m][m], double b[m][m], double result[m][m]) {
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < m; ++j) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}


#define ALPHA  (1e-10)
#define ITERATIONS (200)
void matrix_inverse(size_t m, double matrix[static m][m], double inverse[m][m]) {
    double identity_2[m][m];
    double intermediate[m][m];
    double intermediate_2[m][m];
    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < m; ++j) {
            identity_2[i][j] = 0;
        }
        identity_2[i][i] = 2;
    }

    // Initialize inverse to transpose of input.
    matrix_transpose(m, matrix, inverse);
    for(size_t i = 0; i < m; ++i) {
        scale_row(m, m, i, ALPHA, inverse);
    }

    for(size_t i = 0; i < ITERATIONS; ++i) {
        matrix_multiplication(m, matrix, inverse, intermediate);
        matrix_subtraction(m, identity_2, intermediate, intermediate_2);
        matrix_multiplication(m, inverse, intermediate_2, intermediate);
        matrix_copy(m, intermediate, inverse);
    }

}

void print_array(size_t length, double x[static length]) {
    printf("[ ");
    for(size_t i = 0; i < length; ++i) {
        printf("%f ", x[i]);
    }
    printf("]\n");
}

void print_matrix(size_t m, size_t n, double x[static m][n]) {
    for(size_t i = 0; i < m; ++i) {
        print_array(n, x[i]);
    }
    printf("\n");
}

bool approx_equal(double x, double y) {
    return fabs(x-y) < 1e-5;
}
bool approx_equal_vector(size_t length, double x[static length], double y[static length]) {
    for(size_t i = 0; i < length; i++) {
        if(approx_equal(x[i], y[i]))
            continue;
        printf("Comparison failed at index %lu\n", i);
        printf("x=");
        print_array(length, x);
        printf("y=");
        print_array(length, y);
        return false;
    }

    return true;
}
bool approx_equal_matrix(size_t m, size_t n, double x[static m][n], double y[static m][n]) {
    for(size_t i = 0; i < m; ++i) {
        if(approx_equal_vector(n, x[i], y[i]))
            continue;
        printf("Comparison failed at row %lu\n", i);
        printf("x=");
        print_matrix(m, n, x);
        printf("y=");
        print_matrix(m, n, y);
        return false;
    }

    return true;
}

void test_dot_product(void) {
    double vector_1[] = {1.5, 2.0, 5};
    double vector_2[] = {-0.5, 8, -2};
    assert(approx_equal(dot_product(3, vector_1, vector_2), 1.5*-0.5 + 2*8 + 5*-2));
    assert(approx_equal(dot_product(3, vector_2, vector_1), 1.5*-0.5 + 2*8 + 5*-2));
}

void test_cross_product(void) {
    double vector_1[] = {1.5, 2.0, 5};
    double vector_2[] = {-0.5, 8, -2};
    double result[3] = {0};
    double expected_1[] = {-44, 0.5, 13};
    cross_product(vector_1, vector_2, result);
    assert(approx_equal_vector(sizeof(vector_1)/sizeof(vector_1[0]), result,
        expected_1));
    double expected_2[] = {44, -0.5, -13};
    cross_product(vector_2, vector_1, result);
    assert(approx_equal_vector(sizeof(vector_1)/sizeof(vector_1[0]), result,
        expected_2));
}

void test_matrix_vector_product(void) {
    double matrix[3][3] = {
        {1, 2, 3},
        {-1, -2, -3},
        {2, 4, 6},
    };
    double vector[] = {
        0.5, -0.5, 2
    };
    double result[3] = {0};
    double expected[] = {
        1*0.5+2*-0.5+3*2,
        -1*0.5-2*-0.5-3*2,
        2*0.5+4*-0.5+2*6
    };
    matrix_vector_product(3, 3, matrix, vector, result);
    assert(approx_equal_vector(sizeof(expected) / sizeof(expected[0]), result, expected));
}

void test_gauss_elimination(void) {
    double matrix[3][3] = {
        {2, 4, 8},
        {1, 4, 2},
        {-1, 2, 10},
    };
    double expected[3][3] = {
        {1, 2, 4},
        {0, 1, -1},
        {0, 0, 1},
    };
    gauss_elimination(3, 3, matrix);
    assert(approx_equal_matrix(3, 3, matrix, expected));

    double matrix_2[2][3] = {
        {2, 4, 8},
        {1, 4, 2},
    };
    double expected_2[2][3] = {
        {1, 2, 4},
        {0, 1, -1},
    };
    gauss_elimination(2, 3, matrix_2);
    assert(approx_equal_matrix(2, 3, matrix_2, expected_2));

}

void test_matrix_inverse(void) {
    double matrix[2][2] = {
        {4,7},
        {2,6},
    };
    double result[2][2] = {};
    double expected[2][2] = {
        {0.6, -0.7},
        {-0.2, 0.4},
    };
    matrix_inverse(2, matrix, result);
    assert(approx_equal_matrix(2, 2, result, expected));

    double matrix_2[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 2, 9},
    };
    double result_2[3][3] = {};
    double expected_2[3][3] = {
        {-11.0/12, 1.0/3, 1.0/12},
        {-1.0/6, 1.0/3, -1.0/6},
        {3.0/4, -1.0/3, 1.0/12},
    };
    matrix_inverse(3, matrix_2, result_2);
    assert(approx_equal_matrix(3, 3, result_2, expected_2));
}

int main(void) {
    test_dot_product();
    test_cross_product();
    test_matrix_vector_product();
    test_gauss_elimination();
    test_matrix_inverse();
    printf("Complete.\n");
    return EXIT_SUCCESS;
}