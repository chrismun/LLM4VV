#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host pointer to a device memory region
    int *host_ptr = (int *)malloc(sizeof(int) * N);
    int *device_ptr = (int *)malloc(sizeof(int) * N);

    // Initialize the host and device pointers
    for (int i = 0; i < N; i++) {
        host_ptr[i] = i;
        device_ptr[i] = i;
    }

    // Map the host pointer to the device memory region
    acc_map(host_ptr, device_ptr, N * sizeof(int));

    // Unmap the host pointer from the device memory region
    acc_unmap(host_ptr, device_ptr, N * sizeof(int));

    // Verify that the host pointer is still valid
    for (int i = 0; i < N; i++) {
        if (host_ptr[i] != i) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(host_ptr);
    free(device_ptr);

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
    return failcode;
}