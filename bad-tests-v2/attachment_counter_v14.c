#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: attachment counter
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = test1();
        if (err != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}

int test1() {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    // Initialize arrays
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
        b[i] = 0;
    }

    // Attach arrays to device
    #pragma acc enter data copyin(a[0:10])
    #pragma acc enter data copyin(b[0:10])

    // Increment attachment counter
    #pragma acc update device(a[0:10])
    #pragma acc update device(b[0:10])

    // Check attachment counter
    int counter = 0;
    #pragma acc update self(counter)
    if (counter != 2) {
        err = 1;
    }

    // Detach arrays from device
    #pragma acc exit data delete(a[0:10])
    #pragma acc exit data delete(b[0:10])

    // Check attachment counter again
    #pragma acc update self(counter)
    if (counter != 0) {
        err = 1;
    }

    free(a);
    free(b);

    return err;
}