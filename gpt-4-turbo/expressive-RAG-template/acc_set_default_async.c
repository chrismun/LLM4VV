#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Adjust these values as necessary for your testing framework
#define SEED 12345
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

#ifndef T1
// T1: acc_set_default_async, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *hostArray = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    int *resultArray = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        hostArray[i] = i;
    }

    // Set a custom default async queue
    int default_async_queue = 1;
    acc_set_default_async(default_async_queue);

    // Perform parallel operation without specifying an async queue
    #pragma acc parallel loop copyin(hostArray[0:NUM_ELEMENTS]) copyout(resultArray[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        resultArray[i] = hostArray[i] + 1;
    }

    // Wait for completion of operations in the default async queue
    acc_wait(default_async_queue);

    // Validate the operation
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        if (resultArray[i] != hostArray[i] + 1) {
            err++;
            break;
        }
    }

    free(hostArray);
    free(resultArray);

    // Reset default async queue to initial value
    acc_set_default_async(acc_async_default);

    return err;
}
#endif

int main() {
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test1() != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode |= (1 << 0); // Bitwise OR to set the corresponding bit for failure
    }    
#endif
    return failcode;
}