#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "../1/sort_double.h"

#define MIN_RANGE (-1000.0)
#define MAX_RANGE (1000.0)

void generate_random_sequence(size_t n, double sequence[n]) {
    for(size_t i = 0; i < n; ++i) {
        sequence[i] = MIN_RANGE + (MAX_RANGE - MIN_RANGE) * rand() / RAND_MAX;
    }
}

#define MS_IN_S (1E3)
#define MS_IN_NS (1E-6)
#define NS_IN_S (1E9)
long long unsigned difference_ms(struct timespec* start, struct timespec* end) {
    assert(end->tv_sec > start->tv_sec ||
        (end->tv_sec == start->tv_sec && end->tv_nsec > start->tv_nsec));
    
    double tv_sec_diff = end->tv_sec - start->tv_sec;
    double tv_nsec_diff = end->tv_nsec - start->tv_nsec;
    return (tv_sec_diff) * NS_IN_S + (tv_nsec_diff);
}


int main(int argc, char* argv[argc + 1]) {
    if(argc < 2) {
        printf("Need to provide numbers of elements to time.\n");
        return EXIT_FAILURE;
    }

    // Seed random number generator with the current time.
    srand(time(0));

    for(size_t i = 1; i < argc; ++i) {
        size_t number_of_elements = strtoul(argv[i], 0, 10);
        double sequence[number_of_elements];
        generate_random_sequence(number_of_elements, sequence);
        
        struct timespec start_time = {0};
        struct timespec end_time = {0};
        if(!timespec_get(&start_time, TIME_UTC)) exit(EXIT_FAILURE);
        merge_sort(number_of_elements, sequence);
        if(!timespec_get(&end_time, TIME_UTC)) exit(EXIT_FAILURE);
        assert(is_sorted(number_of_elements, sequence));
        printf("Took %llu ns to quick sort %lu elements\n",
            difference_ms(&start_time, &end_time), number_of_elements);
    }

    return EXIT_SUCCESS;
}