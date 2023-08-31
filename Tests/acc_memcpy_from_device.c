#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create a source and destination buffer on the host
    int *src = (int *)malloc(sizeof(int) * 10);
    int *dst = (int *)malloc(sizeof(int) * 10);

    // Initialize the source buffer with random values
    for (int i = 0; i < 10; i++) {
        src[i] = rand();
    }

    // Copy the source buffer to the destination buffer using acc_memcpy
    acc_memcpy(dst, src, sizeof(int) * 10);

    // Check that the destination buffer contains the same values as the source buffer
    for (int i = 0; i < 10; i++) {
        if (dst[i] != src[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the source and destination buffers
    free(src);
    free(dst);

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