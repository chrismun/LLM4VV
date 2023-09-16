#include "acc_testsuite.h"
#ifndef T1
// T1: reference counters, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Define the size of the data arrays
    int size = 100;

    // Allocate memory for the data arrays
    int* dataA = (int*)malloc(size * sizeof(int));
    int* dataB = (int*)malloc(size * sizeof(int));

    // Initialize the data arrays
    for (int i = 0; i < size; i++) {
        dataA[i] = i;
        dataB[i] = 0;
    }

    // Parallel region with reference counter
    #pragma acc data copyin(dataA[0:size]) copyout(dataB[0:size])
    {
        // Update dataB using dataA
        #pragma acc parallel loop
        for (int i = 0; i < size; i++) {
            dataB[i] = dataA[i] + 1;
        }
    }

    // Verify the results
    for (int i = 0; i < size; i++) {
        if (dataB[i] != dataA[i] + 1) {
            err = 1;
            break;
        }
    }

    // Free the memory
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