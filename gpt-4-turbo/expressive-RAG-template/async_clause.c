#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test 1: Verifying async clause
int test1() {
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    float *array1 = (float *)malloc(size * sizeof(float));
    float *array2 = (float *)malloc(size * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        array1[i] = rand() / (float)RAND_MAX;
        array2[i] = 0;
    }

    // Perform operations asynchronously
    int async1 = 1, async2 = 2;

    // Use the 'async' clause to perform data copying and kernel execution asynchronously
    #pragma acc enter data copyin(array1[0:size]) async(async1)
    #pragma acc parallel loop async(async1)
    for (int i = 0; i < size; ++i) {
        array2[i] = array1[i] + 1;
    }
    #pragma acc exit data copyout(array2[0:size]) async(async1)

    // Signal that async operations completed; useful for synchronization.
    #pragma acc wait(async1)

    // Verification step: Check if operations were completed
    #pragma acc enter data copyin(array2[0:size]) async(async2)
    #pragma acc parallel loop async(async2)
    for (int i = 0; i < size; ++i) {
        if (array2[i] != array1[i] + 1) {
            err += 1;
        }
    }
    #pragma acc exit data copyout(array2[0:size]) async(async2)

    #pragma acc wait(async2)

    free(array1);
    free(array2);
    return err;
}

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
    if (failcode == 0) {
        printf("PASS: OpenACC Async Clause Verification\n");
    } else {
        printf("FAIL: OpenACC Async Clause Verification\n");
    }
    return failcode;
}