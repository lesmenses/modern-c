/* 
Union Find problem on forests (disjoint set of trees).
    disjoint -> trees are distinct and don't share nodes.
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void print_forest(size_t nodes, size_t parent[nodes]);

void initialize(size_t nodes, size_t forest[nodes]) {
    for(size_t i = 0; i < nodes; ++i) {
        forest[i] = SIZE_MAX;
    }
}

size_t find(size_t index, size_t nodes, size_t forest[nodes]) {
    size_t root = nodes;
    for(size_t i = 0; i < nodes; ++i) {
        if(forest[index] != SIZE_MAX) {
            index = forest[index];
            continue;
        }
        root = index;
        break;
    }
    if(root == nodes) {
        assert(0 && "Could not find root.");
    }

    return root;
}

void find_replace(size_t index, size_t new_root, size_t nodes, size_t forest[nodes]) {
    if(index >= nodes)
        assert(0 && "Invalid index.");
    if(new_root >= nodes)
        assert(0 && "Invalid new root.");
    
    for(size_t i = 0; i < nodes; ++i) {
        size_t previous_parent = forest[index];
        forest[index] = (index == new_root) ? SIZE_MAX : new_root;
        index = previous_parent;
        if(index == SIZE_MAX)
            break;
    }
    if(index != SIZE_MAX) {
        assert(0 && "No root found on path.");
    }
}

size_t find_compress(size_t index, size_t nodes, size_t forest[nodes]) {
    if(index >= nodes)
        assert(0 && "Invalid index.");
    
    if(forest[index] == SIZE_MAX)
        return index;
    
    forest[index] = find_compress(forest[index], nodes, forest);

    return forest[index];
}

void forest_union(size_t element_a, size_t element_b, size_t nodes, size_t forest[nodes]) {
    if(element_a >= nodes || element_b >= nodes)
        assert(0 && "Invalid element_a or element_b.");
    
    find_replace(element_b, find_compress(element_a, nodes, forest), nodes, forest);
}

void test_find() {
    size_t parent_1[5] = {
        2,
        0,
        SIZE_MAX,
        4,
        2,
    };
    assert(find(0, 5, parent_1) == 2);
    assert(find(1, 5, parent_1) == 2);
    assert(find(2, 5, parent_1) == 2);
    assert(find(3, 5, parent_1) == 2);
    assert(find(4, 5, parent_1) == 2);

    size_t parent_2[5] = {
        SIZE_MAX,
        0,
        1,
        SIZE_MAX,
        3,
    };
    assert(find(0, 5, parent_2) == 0);
    assert(find(1, 5, parent_2) == 0);
    assert(find(2, 5, parent_2) == 0);
    assert(find(3, 5, parent_2) == 3);
    assert(find(4, 5, parent_2) == 3);
}

bool is_forests_equal(size_t nodes, size_t parent_1[nodes], size_t parent_2[nodes]) {
    for(size_t i = 0; i < nodes; ++i) {
        if(parent_1[i] == parent_2[i])
            continue;
        printf("Comparison failed at index %lu\n", i);
        print_forest(nodes, parent_1);
        print_forest(nodes, parent_2);
        return false;
    }

    return true;
}

void print_forest(size_t nodes, size_t parent[nodes]) {
    printf("Forest: [ ");
    for(size_t i = 0; i < nodes; ++i) {
        printf("%lu ", parent[i]);
    }
    printf(" ]\n");
}

void test_find_replace() {
    size_t parent_1[5] = {
        SIZE_MAX,
        0,
        1,
        2,
        3
    };
    size_t expected_1[5] = {
        2,
        2,
        SIZE_MAX,
        2,
        3,
    };
    find_replace(3, 2, 5, parent_1);
    assert(is_forests_equal(5, parent_1, expected_1));
}

void test_find_compress() {
    size_t parent_1[5] = {
        SIZE_MAX,
        0,
        1,
        2,
        3
    };
    size_t expected_1[5] = {
        SIZE_MAX,
        0,
        0,
        0,
        3,
    };
    find_compress(3, 5, parent_1);
    assert(is_forests_equal(5, parent_1, expected_1));
}

void test_forest_union() {
    size_t parent_1[10] = {
        SIZE_MAX,
        0,
        0,
        1,
        SIZE_MAX,
        4,
        5,
        4,
        5,
        4,
    };
    size_t expected_1[10] = {
        4,
        0,
        4,
        1,
        SIZE_MAX,
        4,
        5,
        4,
        4,
        4
    };
    forest_union(8, 2, 10, parent_1);
    assert(is_forests_equal(10, parent_1, expected_1));
}

int main(void) {
    test_find();
    test_find_replace();
    test_find_compress();
    test_forest_union();
    printf("Complete.\n");
    return EXIT_SUCCESS;
}