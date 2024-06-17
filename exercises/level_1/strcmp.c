#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LENGTH (5UL)
signed bounded_strcmp(size_t s0_length, char const s0[static s0_length], size_t s1_length, char const s1[static s1_length]) {
    void* s0_null = memchr(s0, 0, s0_length);
    void* s1_null = memchr(s1, 0, s1_length);
    if(!s0_null || !s1_null) {
        assert(0 && "Unterminated string\n");
    }
    // Plus one s.t. we include \0 in the comparison.
    // i.e. if s1 is longer, the result of memcmp will match because
    // s0[-1] = \0 which is the min char, so it will be smaller than
    // s1 always.
    ptrdiff_t s0_bytes = s0_null - (void*)s0 + 1;
    ptrdiff_t s1_bytes = s1_null - (void*)s1 + 1;
    size_t check_bytes = s0_bytes < s1_bytes ? s0_bytes : s1_bytes;
    return memcmp(s0, s1, check_bytes);
}

int main(void) {
    char string_1[] = "Jay";
    char string_2[] = "Jay";
    assert(bounded_strcmp(sizeof(string_1), string_1,
        sizeof(string_2), string_2) == 0);

    char string_3[] = "Jays";
    assert(bounded_strcmp(sizeof(string_1), string_1,
        sizeof(string_3), string_3) < 0);
    assert(bounded_strcmp(sizeof(string_3), string_3, sizeof(string_1), string_1) > 0);

    string_3[3] = '\0';
    assert(bounded_strcmp(sizeof(string_1), string_1,
        sizeof(string_3), string_3) == 0);

    // This should fail.
    // char string_unbounded[3] = {'b', 'r', 'o'};
    // bounded_strcmp(sizeof(string_1), string_1, sizeof(string_unbounded), string_unbounded);

}