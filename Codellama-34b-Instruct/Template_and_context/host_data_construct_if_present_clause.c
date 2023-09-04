#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int *dev_mem = (int *)acc_malloc(sizeof(int));
    if (dev_mem == NULL) {
        err = 1;
    }

    // Create a host memory region
    int *host_mem = (int *)malloc(sizeof(int));
    if (host_mem == NULL) {
        err = 1;
    }

    // Initialize the host memory region
    for (int i = 0; i < 10; i++) {
        host_mem[i] = i;
    }

    // Copy the host memory region to the device memory region
    acc_memcpy(dev_mem, host_mem, sizeof(int));

    // Create a host_data construct with the if_present clause
    acc_host_data(dev_mem, host_mem, sizeof(int), if_present);

    // Check if the host memory region is present in the device memory region
    if (acc_is_present(dev_mem, host_mem, sizeof(int)) == 0) {
        err = 1;
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