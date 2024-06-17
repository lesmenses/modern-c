#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

typedef struct queue {
    size_t* array;
    size_t n;
    size_t insert_i;
    size_t remove_i;
} queue_t;

void init_queue(size_t n, size_t array[static n], queue_t* queue) {
    queue->array = array;
    queue->n = n;
    queue->insert_i = 0;
    queue->remove_i = 0;
}

bool is_empty(queue_t* queue) {
    return queue->insert_i == queue->remove_i;
}

bool is_full(queue_t* queue) {
    return queue->insert_i - queue->remove_i == queue->n;
}

void print_queue(queue_t* queue) {
    printf("Queue: insert_i=%lu remove_i=%lu\n", queue->insert_i, queue->remove_i);
    printf("[ ");
    for(size_t i = 0; i < queue->n; ++i) {
        printf("%lu ", queue->array[i]);
    }
    printf("]\n");
}

void enqueue(queue_t* queue, size_t value) {
    if(is_full(queue)) {
        printf("Queue full.\n");
        print_queue(queue);
        return;
    }

    queue->array[queue->insert_i % queue->n] = value;
    ++queue->insert_i;
}

size_t dequeue(queue_t* queue) {
    if(is_empty(queue)) {
        printf("Queue empty.\n");
        print_queue(queue);
        return SIZE_MAX;
    }

    size_t value = queue->array[queue->remove_i % queue->n];
    ++queue->remove_i;
    return value;
}

bool bfs(size_t start_node, size_t end_node, size_t n, bool adjacency[static n][n]) {
    bool visited[n];
    memset(visited, 0, n);
    size_t array[n*(n-1)];
    queue_t to_visit = {0};
    init_queue(n*(n-1), array, &to_visit);

    enqueue(&to_visit, start_node);
    while(!is_empty(&to_visit)) {
        size_t node = dequeue(&to_visit);
        visited[node] = true;
        if(node == end_node) {
            return true;
        }
        for(size_t i = 0; i < n; ++i) {
            if(!adjacency[node][i]) continue;
            if(visited[i]) continue;

            enqueue(&to_visit, i);
        }
    }

    return false;
}


bool bfs_recursive(size_t start_node, size_t end_node, size_t n, bool adjacency[static n][n], bool visited[static n]) {
    if(visited[start_node]) return false;
    if(start_node == end_node) return true;

    visited[start_node] = true;

    for(size_t i = 0; i < n; ++i) {
        if(!adjacency[start_node][i]) continue;
        if(visited[i]) continue;
        if(bfs_recursive(i, end_node, n, adjacency, visited))
            return true;
    }

    return false;
}

void find_nodes_in_component(size_t start_node, size_t n, bool adjacency[static n][n], bool visited[static n]) {
    if(visited[start_node]) return;
    visited[start_node] = true;

    for(size_t i = 0; i < n; ++i) {
        if(!adjacency[start_node][i] && !adjacency[i][start_node]) continue;
        if(visited[i]) continue;
        find_nodes_in_component(i, n, adjacency, visited);
    }
}

size_t find_connected_components(size_t n, bool adjacency[static n][n]) {
    bool is_in_component[n];
    memset(is_in_component, 0, n);
    size_t result = 0;
    for(size_t i = 0; i < n; ++i) {
        if(is_in_component[i]) continue;
        ++result;
        bool nodes_in_component[n];
        memset(nodes_in_component, 0, n);
        find_nodes_in_component(i, n, adjacency, nodes_in_component);
        for(size_t j = 0; j < n; ++j) {
            is_in_component[j] |= nodes_in_component[j];
        }

        printf("Component %lu [ ", result);
        for(size_t j = 0; j < n; ++j) {
            if(!nodes_in_component[j]) continue;
            printf("%lu ", j);
        }
        printf("]\n");
    }
    printf("\n");

    return result;
}

bool is_all_nodes_visited(size_t n, bool visited[static n]) {
    for(size_t i = 0; i < n; ++i) {
        if(!visited[i]) return false;
    }

    return true;
}

void _find_spanning_tree(size_t last_node, size_t node, size_t n, bool adjacency[static n][n], bool visited[static n],
    size_t tree[static n]) {
    if(visited[node]) return;
    visited[node] = true;
    tree[node] = last_node;

    for(size_t i = 0; i < n; ++i) {
        if(!adjacency[node][i]) continue;
        if(visited[i]) continue;

        _find_spanning_tree(node, i, n, adjacency, visited, tree);
    }
}

bool find_spanning_tree(size_t n, bool adjacency[static n][n], size_t tree[static n]) {
    for(size_t i = 0; i < n; ++i) {
        bool visited[n];
        memset(visited, 0, n);
        _find_spanning_tree(SIZE_MAX, i, n, adjacency, visited, tree);

        bool is_spanning_tree = true;
        for(size_t i = 0; i < n; ++i) {
            is_spanning_tree &= visited[i];
        }
        if(is_spanning_tree) return true;
    }

    return false;
}

void test_bfs(void) {
    printf("Testing bfs.\n");
    bool adjacency_1[3][3] = {
        {false, true, true},
        {false, false, false},
        {false, false, false},
    };
    assert(bfs(0, 2, 3, adjacency_1));
    assert(bfs(0, 1, 3, adjacency_1));
    assert(!bfs(1, 2, 3, adjacency_1));
    assert(!bfs(1, 0, 3, adjacency_1));
}

void test_bfs_recursive(void) {
    printf("Testing bfs recursive.\n");
    bool adjacency_1[3][3] = {
        {false, true, true},
        {false, false, false},
        {false, false, false},
    };
    bool visited[3] = {0};
    assert(bfs_recursive(0, 2, 3, adjacency_1, visited));
    memset(visited, 0, 3);
    assert(bfs_recursive(0, 1, 3, adjacency_1, visited));
    memset(visited, 0, 3);
    assert(!bfs_recursive(1, 2, 3, adjacency_1, visited));
    memset(visited, 0, 3);
    assert(!bfs_recursive(1, 0, 3, adjacency_1, visited));
}

void test_find_connected_components(void) {
    printf("Testing connected components.\n");
    bool adjacency_1[3][3] = {
        {false, true, true},
        {false, false, false},
        {false, false, false},
    };
    assert(find_connected_components(3, adjacency_1) == 1);

    bool adjacency_2[6][6] = {
        {false, true, true, false, false, false},
        {false, false, false, false, false, false},
        {false, false, false, false, false, false},
        {false, false, false, false, true, true},
        {false, false, false, false, false, false},
        {false, false, false, false, false, false},
    };
    assert(find_connected_components(6, adjacency_2) == 2);
}

void test_find_spanning_tree(void) {
    printf("Testing spanning tree.\n");
    bool adjacency_1[3][3] = {
        {false, true, true},
        {false, false, false},
        {false, false, false},
    };
    size_t tree_1[3] = {0};
    size_t expected[3] = {SIZE_MAX, 0, 0};
    assert(find_spanning_tree(3, adjacency_1, tree_1));
    assert(memcmp(tree_1, expected, 3*sizeof(size_t)) == 0);

    bool adjacency_2[6][6] = {
        {false, true, true, false, false, false},
        {false, false, false, false, false, false},
        {false, false, false, false, false, false},
        {false, false, false, false, true, true},
        {false, false, false, false, false, false},
        {false, false, false, false, false, false},
    };
    size_t tree_2[6] = {0};
    assert(!find_spanning_tree(6, adjacency_2, tree_2));

    bool adjacency_3[6][6] = {
        {false, false, false, false, false, false},
        {false, false, false, false, false, false},
        {false, false, false, false, true, false},
        {false, false, true, false, false, true},
        {false, false, false, false, false, false},
        {true, true, false, false, false, false},
    };
    size_t tree_3[6] = {0};
    size_t expected_3[6] = {5, 5, 3, SIZE_MAX, 2, 3};
    assert(find_spanning_tree(6, adjacency_3, tree_3));
    assert(memcmp(tree_3, expected_3, 6*sizeof(size_t)) == 0);
}

int main(void) {
    test_bfs();
    test_bfs_recursive();
    test_find_connected_components();
    test_find_spanning_tree();
    return EXIT_SUCCESS;
}