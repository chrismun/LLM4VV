#include "acc_testsuite.h"

#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    void *dev_mem = acc_malloc(1024);

    // Create a host memory region
    void *host_mem = malloc(1024);

    // Initialize the host memory region
    for (int i = 0; i < 1024; i++) {
        host_mem[i] = i;
    }

    // Copy the host memory region to the device memory region
    acc_memcpy_to_device(dev_mem, host_mem, 1024);

    // Verify that the device memory region contains the same data as the host memory region
    for (int i = 0; i < 1024; i++) {
        if (dev_mem[i] != host_mem[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory region
    acc_free(dev_mem);

    // Free the host memory region
    free(host_mem);

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