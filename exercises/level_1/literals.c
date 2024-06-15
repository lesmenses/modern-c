#include <stdio.h>
#include <sys/types.h>

int main(void) {
    unsigned int u_max = 0-1;
    printf("-1U=%u Unsigned max=%u\n", -1U, u_max);

    unsigned long ul_max = 0-1;
    printf("-1UL=%lu Unsigned long max=%lu\n", -1UL, ul_max);

    unsigned long long ull_max = 0-1;
    printf("-1ULL=%llu Unsigned long long max=%llu\n", -1ULL, ull_max);
}