#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create two arrays of random integers
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Copy the contents of a to b using acc memcpy d2d
    acc_memcpy_d2d(a, b, sizeof(int) * 10);

    // Check that the contents of a and b are the same
    for (int i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}