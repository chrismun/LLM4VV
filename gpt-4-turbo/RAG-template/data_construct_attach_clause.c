#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: {data_construct_attach_clause}, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    // Host-side pointer
    int* hostArray;
    int arraySize = 1024;
    hostArray = (int*)malloc(arraySize * sizeof(int));

    // Initialize array with random values
    for (int i = 0; i < arraySize; i++) {
        hostArray[i] = rand() % 100;
    }

    // Attach the dynamically allocated array to a data region and modify its value
#pragma acc data copy(hostArray[0:arraySize]) attach(hostArray[0:arraySize])
    {
#pragma acc parallel loop
        for (int i = 0; i < arraySize; i++) {
            hostArray[i] += 1; // Increment each element to test the effect of the attach clause
        }
    }

    // Verify the modification is reflected back on the host
    for (int i = 0; i < arraySize; i++) {
        if (hostArray[i] != (i + 1)) { 
            err += 1; // Error if the value is not incremented as expected
        }
    }

    free(hostArray); // Clean up

    return err;
}
#endif

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
    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    return failcode;
}