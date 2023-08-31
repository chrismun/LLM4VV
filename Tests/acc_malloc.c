#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory using acc_malloc
    int *ptr = (int *)acc_malloc(sizeof(int) * 10);
    if (ptr == NULL) {
        err = 1;
    }

    // Check if the memory is correctly allocated
    if (ptr[0] != 0 || ptr[1] != 0 || ptr[2] != 0 || ptr[3] != 0 || ptr[4] != 0 || ptr[5] != 0 || ptr[6] != 0 || ptr[7] != 0 || ptr[8] != 0 || ptr[9] != 0) {
        err = 1;
    }

    // Free the memory using acc_free
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