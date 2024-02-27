#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:{feature}, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Define test data and variables
    const size_t bytes = sizeof(int) * 1024; // Arbitrary size for testing.
    int *host_array_src, *host_array_dest;
    int *device_array_src, *device_array_dest;

    // Allocate and initialize memory on the host
    host_array_src = (int*)malloc(bytes);
    host_array_dest = (int*)malloc(bytes);
    for (size_t i = 0; i < bytes / sizeof(int); ++i) {
        host_array_src[i] = rand();
        host_array_dest[i] = 0; // Initialize destination with zeros
    }

    // Allocate memory on the device
    device_array_src = (int*)acc_malloc(bytes);
    device_array_dest = (int*)acc_malloc(bytes);

    if (!device_array_src || !device_array_dest) {
        // Error allocating memory on the device
        err++;
        goto cleanup;
    }

    // Copy host data to the device source array
    acc_memcpy_to_device(device_array_src, host_array_src, bytes);

    // Execute device to device copy
    acc_memcpy_device(device_array_dest, device_array_src, bytes);

    // Copy back to host for verification
    acc_memcpy_from_device(host_array_dest, device_array_dest, bytes);

    // Verify data integrity
    for (size_t i = 0; i < bytes / sizeof(int); ++i) {
        if (host_array_src[i] != host_array_dest[i]) {
            err++; // Data mismatch
            break;
        }
    }

cleanup:
    free(host_array_src);
    free(host_array_dest);
    acc_free(device_array_src);
    acc_free(device_array_dest);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    printf("Test %s\n", failcode ? "FAILED" : "PASSED");
    return failcode;
}