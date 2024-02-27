#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const size_t dataSize = 1024; // Change according to needs.
    int *hostData = (int *)malloc(dataSize * sizeof(int));
    // Initialize host data.
    for (size_t i = 0; i < dataSize; ++i) {
        hostData[i] = rand() % 100;
    }

    // Allocate memory on device and copy data from host.
    int *deviceData = (int *)acc_malloc(dataSize * sizeof(int));
    if (deviceData == NULL) {
        printf("Device memory allocation failed\n");
        err++;
    } else {
        acc_memcpy_to_device(deviceData, hostData, dataSize * sizeof(int));

        // Free the allocated memory.
        acc_free(deviceData);

        // Try accessing the freed memory (Not recommended in real applications. This is just for testing.)
        // Optional test: After free, accessing device memory might lead to undefined behavior. Skipping this step.
    }

    // Test freeing a NULL pointer should not cause any problem
    int *nullPtr = NULL;
    acc_free(nullPtr);

    free(hostData); // Free host memory
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    
    // Initializing OpenACC runtime
    acc_init(acc_device_default);

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    // Finalize OpenACC runtime
    acc_shutdown(acc_device_default);

    return failcode;
}