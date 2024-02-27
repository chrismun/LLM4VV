#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Variables for host and device pointers
    int *hostData;
    int **deviceDataPtr, *deviceData;

    // Allocate memory on the host
    hostData = (int *)malloc(sizeof(int) * 10);
    deviceDataPtr = (int **)acc_malloc(sizeof(int*));

    // Initialize host data
    for (int i = 0; i < 10; ++i) {
        hostData[i] = rand() % 100;
    }

    // Point the device pointer to the host memory
    *deviceDataPtr = hostData;

    // Attach the memory to the device
    acc_attach((h_void **)deviceDataPtr);

    // Modify the data on the device using an OpenACC kernel
    #pragma acc parallel loop copyin(hostData[0:10]) present(deviceDataPtr[0:1])
    for (int i = 0; i < 10; ++i) {
        (*deviceDataPtr)[i] += 5; // Increment each element by 5
    }

    // Detach the data from the device
    acc_detach((h_void **)deviceDataPtr);

    // Verify the modification made on the device is reflected on the host
    for (int i = 0; i < 10; ++i) {
        if (hostData[i] % 5 != 0) { // Check if modifications are present
            err++;
            break;
        }
    }

    // Clean up
    acc_free(deviceDataPtr);
    free(hostData);

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