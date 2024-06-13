
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[argc + 1]) {
    if(argc != 2) {
        printf("Need one input.\n");
        return EXIT_FAILURE;
    }

    switch(argv[1][0]) {
        case 'm':
            puts("This is a magpie.");
            break;
        case 'r':
            puts("This is a raven.");
            break;
        case 'j':
            puts("This is a jay.");
            break;
        case 'c':
            puts("This is a chough.");
            break;
        default:
            puts("This is an unknown corvid.");
    }

}