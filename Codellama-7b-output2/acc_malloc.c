#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory using acc_malloc
    void *ptr = acc_malloc(1024);
    if (ptr == NULL) {
        err = 1;
    }

    // Check if the memory is accessible
    if (ptr[0] != 0) {
        err = 1;
    }

    // Free the memory
    acc_free(ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}