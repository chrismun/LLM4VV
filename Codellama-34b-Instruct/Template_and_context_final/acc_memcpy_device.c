#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory for the source and destination arrays
    int *src = (int *)acc_malloc(sizeof(int) * 10);
    int *dest = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the source array with random values
    for (int i = 0; i < 10; i++) {
        src[i] = rand() % 100;
    }

    // Copy the source array to the destination array using acc_memcpy_device
    acc_memcpy_device(dest, src, sizeof(int) * 10);

    // Check that the destination array contains the same values as the source array
    for (int i = 0; i < 10; i++) {
        if (dest[i] != src[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the source and destination arrays
    acc_free(src);
    acc_free(dest);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}