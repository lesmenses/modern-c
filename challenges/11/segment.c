#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../include/png.h"
#include "../4/union_find.h"

typedef struct segment segment;
struct segment {
    size_t nodes;
    uint64_t sum;
};


#define INDEX(row, col, cols) ((row)*(cols) + (col))
double segment_mean(segment* segment) {
    return (double)segment->sum / segment->nodes;
}

bool merge_segments(size_t index, size_t neighbour, size_t nodes,
        size_t forest[static nodes], segment segments[static nodes], double merge_value) {
    size_t index_root = find(index, nodes, forest);
    size_t neighbour_root = find(neighbour, nodes, forest);
    if(index_root == neighbour_root) {
        return false;
    }
    if(fabs(segment_mean(&segments[index_root]) -
        segment_mean(&segments[neighbour_root])) > merge_value) {
        return false;
    }

    size_t new_root = forest_union(index, neighbour, nodes, forest);
    segments[new_root].nodes = segments[index_root].nodes + segments[neighbour_root].nodes;
    segments[new_root].sum = segments[index_root].sum + segments[neighbour_root].sum;

    return true;
}

void segment_image(size_t width, size_t height, png_bytep buffer, double merge_value) {
    // Initialize the structure used to partition image.
    // Each pixel starts in its own segment.
    size_t pixels = width*height;
    size_t forest[pixels];
    segment* segments = malloc(sizeof(segment) * pixels);
    for(size_t i = 0; i < pixels; ++i) {
        forest[i] = SIZE_MAX;
        segments[i].nodes = 1;
        segments[i].sum = buffer[i]; 
    }

    while(1) {
        size_t merges = 0;
        for(size_t i = 0; i < height; ++i) {
            for(size_t j = 0; j < width; ++j) {
                // Check left pixel for possible merge.
                if(j && merge_segments(INDEX(i, j, width), INDEX(i, j-1, width),
                    pixels, forest, segments, merge_value)) {
                    ++merges;
                }
                // Check up pixel for possible merge
                if(i && merge_segments(INDEX(i, j, width), INDEX(i-1, j, width),
                        pixels, forest, segments, merge_value)) {
                    ++merges;
                }
            }
        }

        if(!merges) break;
    }

    // Modify the value of each pixel with the mean of the segment.
    for(size_t i = 0; i < pixels; ++i) {
        size_t root = find(i, pixels, forest);
        buffer[i] = segments[root].sum / segments[root].nodes;
    }

    free(segments);
}

int main(int argc, char* argv[argc + 1]) {
    if(argc != 4) {
        fprintf(stderr, "Need to supply input, output, merge value.\n");
        return EXIT_FAILURE;
    }

    printf("Reading image.\n");
    // Read the image in as grayscale.
    png_image image = {0};
    image.version = PNG_IMAGE_VERSION;
    if(!png_image_begin_read_from_file(&image, argv[1])) {
        fprintf(stderr, "Image read init failed.\n");
        fprintf(stderr, "libpng error: %s\n", image.message);
        return EXIT_FAILURE;
    }

    image.format = PNG_FORMAT_GRAY;
    size_t buffer_size = PNG_IMAGE_SIZE(image);
    png_bytep buffer = malloc(PNG_IMAGE_SIZE(image));
    if(buffer == NULL) {
        png_image_free(&image);
        fprintf(stderr, "Not enough program memory to store image.\n");
        fprintf(stderr, "libpng error: %s\n", image.message);
        return EXIT_FAILURE;
    }

    if(!png_image_finish_read(&image, (void*)0, buffer, 0, (void*)0)) {
        free(buffer);
        fprintf(stderr, "Could not complete read.\n");
        fprintf(stderr, "libpng error: %s\n", image.message);
        return EXIT_FAILURE;
    }
    printf("Finished reading image.\n");

    // Perform segmentation.
    printf("Performing segmentation on the image.\n");
    assert(image.width*image.height == buffer_size);
    segment_image(image.width, image.height, buffer, strtof(argv[3], 0));
    printf("Finished performing segmentation on the image.\n");

    // Write out the modified image.
    printf("Writing image to file.\n");
    if(!png_image_write_to_file(&image, argv[2], 0, buffer, 0, (void*)0)) {
        fprintf(stderr, "Could not write modified image.\n");
        fprintf(stderr, "libpng error: %s\n", image.message);
        return EXIT_FAILURE;
    }
    printf("Finished writing image to file.\n");

    return EXIT_SUCCESS;
}