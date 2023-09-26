#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: acc malloc, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory using acc_malloc
    int* data = (int*)acc_malloc(sizeof(int) * N);

    // Check if memory allocation was successful
    if (!data) {
        err = 1;
    }

    // Free the allocated memory
    acc_free(data);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}