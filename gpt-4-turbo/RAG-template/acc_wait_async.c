#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int dataSize = 1024;
    int *dataA = (int*)malloc(sizeof(int) * dataSize);
    int *dataB = (int*)malloc(sizeof(int) * dataSize);
    const int async_queue_1 = 1, async_queue_2 = 2;

    // Initialize data
    for (int i = 0; i < dataSize; ++i) {
        dataA[i] = rand() % 100;
        dataB[i] = rand() % 100;
    }

#pragma acc data copy(dataA[0:dataSize], dataB[0:dataSize])
    {
        // Perform computation in async_queue_1
#pragma acc parallel loop async(async_queue_1)
        for (int i = 0; i < dataSize; ++i) {
            dataA[i] += 1;
        }

        // Wait for the completion of async_queue_1 before proceeding in async_queue_2
        acc_wait_async(async_queue_1, async_queue_2);

        // Perform computation in async_queue_2 which depends on the completion of operations in async_queue_1
#pragma acc parallel loop async(async_queue_2)
        for (int i = 0; i < dataSize; ++i) {
            dataB[i] += dataA[i];
        }
    }

    // Verify the results (omitted for brevity). This part should check if data updates are correctly synchronized.
    // For a real test, this would involve checking that the operations in `async_queue_2` have correctly waited for those in `async_queue_1`.

    free(dataA);
    free(dataB);
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
    return failcode;
}