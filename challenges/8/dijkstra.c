#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

size_t find_index_of_smallest_distance(size_t n, size_t unvisited_distances[static n], bool visited[static n]) {
    size_t min_distance = SIZE_MAX;
    size_t index = SIZE_MAX;
    for(size_t i = 0; i < n; ++i) {
        if(visited[i]) continue;
        if(unvisited_distances[i] > min_distance) continue;
        min_distance = unvisited_distances[i];
        index = i;
    }
    if(index == SIZE_MAX)
        assert(0 && "Could not find smallest distance.");
    
    return index;
    
}

// Dijkstra's
size_t get_shortest_path_length(size_t start_i, size_t end_i, size_t n, size_t distances[static n][n]) {
    if(start_i == end_i) return 0;

    bool visited[n];
    size_t unvisited_distances[n];
    size_t path_lengths[n];
    for(size_t i = 0; i < n; ++i) {
        unvisited_distances[i] = SIZE_MAX;
        path_lengths[i] = SIZE_MAX;
        visited[i] = false;
    }
    unvisited_distances[start_i] = 0;

    for(size_t i = 0; i < n; ++i) {
        size_t node_i = find_index_of_smallest_distance(n, unvisited_distances, visited);
        path_lengths[node_i] = unvisited_distances[node_i];
        // We've reached the node of interest. No point in going further.
        if(node_i == end_i) break;
        visited[node_i] = true;
        // Potentially update unvisited node distances.
        size_t distance = path_lengths[node_i];
        for(size_t j = 0; j < n; ++j) {
            if(visited[j]) continue;
            if(distances[node_i][j] == SIZE_MAX) continue;
            size_t new_distance = distance + distances[node_i][j];
            unvisited_distances[j] = unvisited_distances[j] <= new_distance ? unvisited_distances[j] : new_distance;
        }
    }

    return path_lengths[end_i];
}

void test_get_shortest_path_length(void) {
    printf("Testing dijksta's algorithm.\n");
    size_t distance_matrix[6][6] = {
        {SIZE_MAX, 2, SIZE_MAX, 8, SIZE_MAX, SIZE_MAX},
        {2, SIZE_MAX, SIZE_MAX, 5, 6, SIZE_MAX},
        {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, 9, 3},
        {8, 5, SIZE_MAX, SIZE_MAX, 3, 2},
        {SIZE_MAX, 6, 9, 3, SIZE_MAX, 1},
        {SIZE_MAX, SIZE_MAX, 3, 2, 1, SIZE_MAX},
    };
    assert(get_shortest_path_length(0, 2, 6, distance_matrix) == 12);
    assert(get_shortest_path_length(0, 3, 6, distance_matrix) == 7);
    assert(get_shortest_path_length(0, 4, 6, distance_matrix) == 8);
}

int main(void) {
    test_get_shortest_path_length();
    return EXIT_SUCCESS;
}