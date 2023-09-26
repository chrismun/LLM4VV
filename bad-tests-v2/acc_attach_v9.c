#include "acc_testsuite.h"

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;

    // Create a host pointer to a memory location
    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = 1234;

    // Attach the host pointer to the device
    acc_attach(&host_ptr);

    // Create a device pointer to the same memory location
    int *device_ptr = (int *)acc_malloc(sizeof(int));
    *device_ptr = 5678;

    // Detach the host pointer from the device
    acc_detach(&host_ptr);

    // Check that the device pointer still points to the same memory location
    if (*device_ptr != 5678) {
        err = 1;
    }

    // Free the device memory
    acc_free(device_ptr);

    // Free the host memory
    free(host_ptr);

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