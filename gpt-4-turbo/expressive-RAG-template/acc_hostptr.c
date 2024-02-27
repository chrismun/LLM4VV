#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Define a simple structure for this testsuite
#ifndef T1
//T1:acc_hostptr, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int host_data = rand(); // Initialize with random data
    int *device_ptr = NULL;
    int *host_ptr = NULL;

    // Allocating memory on the device and copying data from the host to device
    device_ptr = acc_malloc(sizeof(int));
    if (device_ptr == NULL) {
        fprintf(stderr, "Failed to allocate device memory.\n");
        return ++err;
    }
    acc_memcpy_to_device(device_ptr, &host_data, sizeof(int));

    // Use acc_hostptr to get the host pointer from the device pointer and validate it
    host_ptr = (int *)acc_hostptr(device_ptr);

    // Verify if returned host_ptr is equal to address of host_data
    if (host_ptr != &host_data) {
        fprintf(stderr, "acc_hostptr did not return the correct host pointer.\n");
        err++;
    }

    // Cleanup
    acc_free(device_ptr);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}