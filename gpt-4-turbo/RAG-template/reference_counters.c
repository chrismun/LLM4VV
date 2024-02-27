#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

// Assuming acc_testsuite.h includes openacc.h, if not, uncomment the line below
// #include <openacc.h>

#ifndef T1
// T1:reference_counters,V:2.7-3.3
int test1() {
    int err = 0;
    const int dataSize = 1024;
    int *hostData = (int*)malloc(sizeof(int) * dataSize);
    srand(SEED);

    // Populate host data
    for (int i = 0; i < dataSize; i++) {
        hostData[i] = rand();
    }

    // Enter data region, implicitly incrementing the structured reference counter
    #pragma acc enter data copyin(hostData[0:dataSize])

    // Use API call to increment dynamic reference counter
    acc_copyin(hostData, sizeof(int) * dataSize);

    // Modify data on the device to simulate computation
    #pragma acc parallel loop present(hostData)
    for (int i = 0; i < dataSize; i++) {
        hostData[i] += 1;
    }

    // Use API call to decrement dynamic reference counter (should not deallocate due to structured counter)
    acc_delete(hostData, sizeof(int) * dataSize);

    // Modify data again to ensure it's still present
    #pragma acc parallel loop present(hostData)
    for (int i = 0; i < dataSize; i++) {
        hostData[i] += 1;
    }

    // Exit data region, should decrement structured reference counter and deallocate due to both counters being zero
    #pragma acc exit data copyout(hostData[0:dataSize])

    // Validate data
    for (int i = 0; i < dataSize; i++) {
        if (hostData[i] != rand() + 2) { // Assuming same rand sequence
            err++;
            break;
        }
    }

    free(hostData);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("There were test failures.\n");
    }
    return failcode;
}