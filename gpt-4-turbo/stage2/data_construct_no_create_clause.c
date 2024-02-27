#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 100

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
// Test the no_create clause by allocating memory on the host but not creating it on
// the device explicitly. Verify by manipulating the data within an OpenACC region
// and checking for unchanged data on the host, as no data should be copied back if it was never created.
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *hostArray = (int *) malloc(size * sizeof(int));

    // Initialize host array
    for (int i = 0; i < size; i++) {
        hostArray[i] = rand() % 100;
    }

    // Attempt to use no_create clause
    #pragma acc data copyin(hostArray[0:size]) no_create(hostArray[0:size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            hostArray[i] += 1; // Modify the data which should not reflect back on the host
        }
    }

    // Verify unchanged data on host to confirm no_create behavior
    for (int i = 0; i < size; i++) {
        if (hostArray[i] % 100 != rand() % 100) {
            err++;
        }
    }

    free(hostArray);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        srand(SEED); // Reset seed for consistency in verification
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("PASS: OpenACC no_create clause appears to be implemented correctly.\n");
    } else {
        printf("FAIL: OpenACC no_create clause may have issues in its implementation.\n");
    }

    return failcode;
}