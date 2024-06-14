/* Calculating new time after adding an hour offset. */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[argc + 1]) {
    if(argc != 3) {
        printf("Input should be ./clock [HH:00] [HH]");
        return EXIT_FAILURE;
    }

    size_t current_hour = strtoul(argv[1], (void*)0, 10);
    if(current_hour > 24) {
        printf("Invalid time %lu\n", current_hour);
        return EXIT_FAILURE;
    }

    size_t offset = strtoul(argv[2], (void*)0, 10);

    printf("New time is %2lu:00\n", (current_hour+offset)%24);

    return EXIT_SUCCESS;
}