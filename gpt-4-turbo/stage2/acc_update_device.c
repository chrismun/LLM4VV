#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// The test suite header is hypothetically included for necessary macros and seed,
// though it's not provided in this context. You may need to adjust or define SEED and NUM_TEST_CALLS.
// #include "acc_testsuite.h"

#ifndef T1
// T1:acc update device,V:2.7-3.3
int test1() {
    int err = 0;
    // Assuming SEED and NUM_TEST_CALLS are defined
    srand(1234); // SEED substitute
    
    int data[10];
    int result[10];
    // Initialize array with some data
    for (int i = 0; i < 10; ++i) {
        data[i] = rand() % 100;
    }

    // Update one of the array elements on the host
    data[5] = 999;

    // Make sure the data is present on the device
    #pragma acc enter data copyin(data)

    // Update the device version of the data array
    acc_update_device(data, sizeof(data));

    // Use the updated data array in a compute region and check if the update is reflected
    #pragma acc parallel loop present(data) copyout(result)
    for (int i = 0; i < 10; i++) {
        result[i] = data[i] * 2;
    }

    // Validate the updated data has been used in the computation
    if (result[5] != 999 * 2) {
        err++;
    }

    // Cleanup: Exit data region
    #pragma acc exit data delete(data)

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // NUM_TEST_CALLS substitute with 1 for simplicity
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}