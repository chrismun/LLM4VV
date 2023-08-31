#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of 100 integers
    int a[100];
    for (int i = 0; i < 100; i++) {
        a[i] = rand() % 100;
    }

    // Copy the array to the device
    #pragma acc enter data copyin(a)

    // Copy the array back to the host
    #pragma acc enter data copyout(a)

    // Delete the array from the device
    #pragma acc delete(a)

    // Check that the array is no longer accessible
    for (int i = 0; i < 100; i++) {
        if (a[i] != 0) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc enter data copyin(test1)

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    #pragma acc exit data copyout(test1)

    return failcode;
}