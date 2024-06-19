/*
    Sorting doubles.
*/

#include <sys/types.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort_double.h"

void quick_sort(size_t length, double array[length]) {
    if(length <= 1) return; // No sorting to do.

    // Choose pivot and move to beginning of array.
    size_t pivot_index = length / 2;
    double pivot_value = array[pivot_index];
    array[pivot_index] = array[0];
    array[0] = pivot_value;

    // Main body of quick sort.
    double* left = array + 1;
    double* right = array + length - 1;
    while (left <= right) {
        if(*left <= pivot_value) {
            ++left;
            continue;
        }
        if(*right > pivot_value) {
            --right;
            continue;
        }

        // Swap left and right values.
        double temp = *right;
        *right = *left;
        *left = temp;
        ++left;
        --right;
    }

    // Swap pivot with the right pointer.
    array[0] = *right;
    *right = pivot_value;

    // Quick sort on each side of the pivot (now pointed to by right).
    quick_sort(right - array, array);
    quick_sort(length - (right - array) - 1, right + 1);

}

void merge_sort(size_t length, double array[length]) {
    if(length == 1) return; // No sorting to do.

    // Merge sort on each of the halves first.
    double* first_half = array;
    double* second_half = array + (length/2);
    merge_sort(length/2, first_half);
    merge_sort(length-(length/2), second_half);

    // Merge the sorted halves.
    size_t first_half_i = 0;
    size_t second_half_i = 0;
    double result[length];
    for(size_t i = 0; i < length; ++i) {
        if(second_half_i >= (length-(length/2))) {
            result[i] = first_half[first_half_i];
            ++first_half_i;
        } else if (first_half_i >= length/2) {
            result[i] = second_half[second_half_i];
            ++second_half_i;
        } else if (first_half[first_half_i] <= second_half[second_half_i]) {
            result[i] = first_half[first_half_i];
            ++first_half_i;
        } else if(first_half[first_half_i] > second_half[second_half_i]) {
            result[i] = second_half[second_half_i];
            ++second_half_i;
        } else {
            assert(0);
        }
    }
    memcpy(array, result, length*sizeof(double));
}


void print_array(size_t length, double values[length]) {
    printf("[");
    for (size_t i = 0; i < length; i++) {
        if(i != 0) {
            printf(", ");
        }
        printf("%.2f", values[i]);
    }
    printf("]\n");
}

bool is_sorted(size_t length, double values[length]) {

    for(int i = 0; i < length; i++) {
        if(i == 0) {
            continue;
        }
        if (values[i-1] > values[i]) {
            printf("ERROR: Following array failed.\n");
            print_array(length, values);
            return false;
        }
    }
    return true;
}

void verify_merge(void) {
    double values_1[2] = {1, 0};
    merge_sort(2, values_1);
    assert(is_sorted(2, values_1));

    double values_2[2] = {1, -1};
    merge_sort(2, values_2);
    assert(is_sorted(2, values_2));

    double values_3[1] = {1};
    merge_sort(1, values_3);
    assert(is_sorted(1, values_3));

    double values_4[] = {23, 10, 54, 8, 4, -10};
    merge_sort(sizeof(values_4)/sizeof(double), values_4);
    assert(is_sorted(sizeof(values_4)/sizeof(double), values_4));

    printf("Verification complete.\n");
}

void verify_quick(void) {
    double values_1[2] = {1, 0};
    quick_sort(2, values_1);
    assert(is_sorted(2, values_1));

    double values_2[2] = {1, -1};
    quick_sort(2, values_2);
    assert(is_sorted(2, values_2));

    double values_3[1] = {1};
    quick_sort(1, values_3);
    assert(is_sorted(1, values_3));

    double values_4[] = {23, 10, 54, 8, 4, -10};
    quick_sort(sizeof(values_4)/sizeof(double), values_4);
    assert(is_sorted(sizeof(values_4)/sizeof(double), values_4));

    double values_5[] = {23, -10, 54, 8, 4, -10};
    quick_sort(sizeof(values_5)/sizeof(double), values_5);
    assert(is_sorted(sizeof(values_5)/sizeof(double), values_5));

    printf("Verification complete.\n");
}

/*
Define INCLUDE via compiler options to disable main
s.t. sort_double can be used by another program.
*/
#ifndef INCLUDE
int main(int argc, char* argv[argc + 1]) {
    if(argc == 1) {
        printf("No data to sort.\n");
        return EXIT_FAILURE;
    }
    if(argc == 2 && !strcmp(argv[1], "verify")) {
        verify_merge();
        verify_quick();
        return EXIT_SUCCESS;
    }

    double data[argc-1];
    for(size_t i = 1; i < argc; ++i) {
        data[i-1] = strtod(argv[i], 0);
    }

    printf("Sorting array: ");
    print_array(argc-1, data);
    merge_sort(argc-1, data);
    printf("Sorted array: ");
    print_array(argc-1, data);
    is_sorted(argc-1, data);

    return EXIT_SUCCESS;
}
#endif