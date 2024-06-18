#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void print_timespec(struct timespec* time) {
    printf("[%ld s, %ld ns]", time->tv_sec, time->tv_nsec);
}

#define NANO_SECONDS_IN_SECOND     (1000000000.0)
double timespec_diff(struct timespec* time_1, struct timespec* time_2) {
    return (time_1->tv_sec - time_2->tv_sec) + (time_1->tv_nsec - time_2->tv_nsec) / NANO_SECONDS_IN_SECOND;
}

#define EPSILON (1E-10)
bool approx_equal(double x, double y) {
    return fabs(x-y) < EPSILON;
}

int main(int argc, char* argv[static argc+1]) {
    if(argc != 5) {
        printf("Need 4 args.\n");
        return EXIT_FAILURE;
    }

    struct timespec time_1 = {.tv_sec=strtol(argv[1], 0, 10), .tv_nsec=strtol(argv[2], 0, 10)};
    struct timespec time_2 = {.tv_sec=strtol(argv[3], 0, 10), .tv_nsec=strtol(argv[4], 0, 10)};
    printf("Time difference is %f s.\n", timespec_diff(&time_1, &time_2));

    return EXIT_SUCCESS;
}