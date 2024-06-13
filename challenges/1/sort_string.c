/*
    Sorting strings.
*/

#include <sys/types.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_array(size_t length, char* values[length]);

void quick_sort(size_t length, char* array[length]) {
    if(length <= 1) return; // No sorting to do.

    // Choose pivot and move to beginning of array.
    size_t pivot_index = length / 2;
    char* pivot_string = array[pivot_index];
    array[pivot_index] = array[0];
    array[0] = pivot_string;

    // Main body of quick sort.
    char** left = array + 1;
    char** right = array + length - 1;
    while (left <= right) {
        if(strcmp(*left, pivot_string) <= 0) {
            ++left;
            continue;
        }
        if(strcmp(*right, pivot_string) > 0) {
            --right;
            continue;
        }

        // Swap left and right values.
        char* temp = *right;
        *right = *left;
        *left = temp;
        ++left;
        --right;
    }

    // Swap pivot with the right pointer.
    array[0] = *right;
    *right = pivot_string;

    // Quick sort on each side of the pivot (now pointed to by right).
    quick_sort(right - array, array);
    quick_sort(length - (right - array) - 1, right + 1);
}

void merge_sort(size_t length, char* array[length]) {
    if(length == 1) return; // No sorting to do.

    // Merge sort on each of the halves first.
    char** first_half = array;
    char** second_half = array + (length/2);
    merge_sort(length/2, first_half);
    merge_sort(length-(length/2), second_half);

    // Merge the sorted halves.
    size_t first_half_i = 0;
    size_t second_half_i = 0;
    char* result[length];
    for(size_t i = 0; i < length; ++i) {
        if(second_half_i >= (length-(length/2))) {
            result[i] = first_half[first_half_i];
            ++first_half_i;
            continue;
        } else if (first_half_i >= length/2) {
            result[i] = second_half[second_half_i];
            ++second_half_i;
            continue;
        }

        int ret = strcmp(first_half[first_half_i], second_half[second_half_i]);
        if(ret <= 0) {
            result[i] = first_half[first_half_i];
            ++first_half_i;
        } else {
            result[i] = second_half[second_half_i];
            ++second_half_i;
        }
    }

    memcpy(array, result, length*sizeof(char*));
}

void print_array(size_t length, char* values[length]) {
    printf("[");
    for (size_t i = 0; i < length; i++) {
        if(i != 0) {
            printf(", ");
        }
        printf("%s", values[i]);
    }
    printf("]\n");
}

void is_sorted(size_t length, char* values[length]) {

    for(int i = 0; i < length; i++) {
        if(i == 0) {
            continue;
        }
        if (strcmp(values[i-1], values[i]) > 0) {
            printf("ERROR: Following array failed.\n");
            print_array(length, values);
            assert(0);
        }
    }
    printf("Check complete.\n");
}

void verify_merge(void) {
    char* strings_1[2] = {"breh", "bruh"};
    merge_sort(sizeof(strings_1)/sizeof(strings_1[0]), strings_1);
    is_sorted(sizeof(strings_1)/sizeof(strings_1[0]), strings_1);

    char* strings_2[2] = {"bruh", "breh"};
    merge_sort(sizeof(strings_2)/sizeof(strings_2[0]), strings_2);
    is_sorted(sizeof(strings_2)/sizeof(strings_2[0]), strings_2);

    char* strings_3[] = {"bruh", "past", "guap", "breh", "karl", "bria", "noah", "chap"};
    merge_sort(sizeof(strings_3)/sizeof(strings_3[0]), strings_3);
    is_sorted(sizeof(strings_3)/sizeof(strings_3[0]), strings_3);
}

void verify_quick(void) {
    char* strings_1[2] = {"breh", "bruh"};
    quick_sort(sizeof(strings_1)/sizeof(strings_1[0]), strings_1);
    is_sorted(sizeof(strings_1)/sizeof(strings_1[0]), strings_1);

    char* strings_2[2] = {"bruh", "breh"};
    quick_sort(sizeof(strings_2)/sizeof(strings_2[0]), strings_2);
    is_sorted(sizeof(strings_2)/sizeof(strings_2[0]), strings_2);

    char* strings_3[] = {"bruh", "past", "guap", "breh", "karl", "bria", "noah", "chap"};
    quick_sort(sizeof(strings_3)/sizeof(strings_3[0]), strings_3);
    is_sorted(sizeof(strings_3)/sizeof(strings_3[0]), strings_3);
}

int main(int argc, char* argv[argc + 1]) {
    if(argc == 1) {
        printf("No data to sort.\n");
        return EXIT_FAILURE;
    }
    if(argc == 2 && strcmp(argv[1], "verify") == 0) {
        verify_merge();
        verify_quick();
        return EXIT_SUCCESS;
    }

    print_array(argc-1, argv+1);
    quick_sort(argc-1, argv+1);
    is_sorted(argc-1, argv+1);
    print_array(argc-1, argv+1);

    return EXIT_SUCCESS;
}