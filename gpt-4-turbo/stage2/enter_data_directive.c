#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Assuming definitions for test suite
#define SEED 12345
#define NUM_TEST_CALLS 10

// T1:enter data directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(sizeof(int) * size);

    // Initialize array
    for (int i = 0; i < size; ++i) {
        a[i] = i;
    }

    // Enter data to the device
    #pragma acc enter data copyin(a[0:size])

    // Dummy operation on the device to test if the data is there
    #pragma acc parallel loop present(a)
    for (int i = 0; i < size; ++i) {
        a[i] = a[i] * 2;
    }

    // Exit data from the device
    #pragma acc exit data copyout(a[0:size])

    // Validate
    for (int i = 0; i < size; ++i) {
        if (a[i] != i * 2) { // Expect each element to be doubled
            err++;
        }
    }

    free(a);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }

    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}