#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SEED 1234
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 1024

// Utility to initialize array
void initialize_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100; // Random integers between 0 and 99
    }
}

int test1() {
    int err = 0;
    srand(SEED);
    int* a = (int*)malloc(ARRAY_SIZE * sizeof(int));

    initialize_array(a, ARRAY_SIZE);

    // Attaching dynamically allocated memory to the device
    #pragma acc enter data copyin(a[0:ARRAY_SIZE])

    // Perform computation on the device
    #pragma acc parallel loop present(a)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] += 1; // Simple operation to verify functionality
    }

    // Copy data back to the host
    #pragma acc exit data copyout(a[0:ARRAY_SIZE])

    // Verification
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (a[i] != (rand() % 100) + 1) { // Considering initial random value plus 1
            err++;
            break;
        }
    }

    free(a);
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test1() != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("PASSED: All tests passed!\n");
    } else {
        printf("FAILED: Some tests failed.\n");
    }

    return failcode;
}