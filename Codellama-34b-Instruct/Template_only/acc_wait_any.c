#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    acc_malloc(&dev_array, sizeof(int) * 10);

    // Create a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Initialize the host array
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Copy the host array to the device array
    acc_memcpy(dev_array, host_array, sizeof(int) * 10);

    // Create a wait directive
    acc_wait_any(dev_array, 10);

    // Check if the wait directive has completed
    if (acc_wait_any(dev_array, 10) != 0) {
        err = 1;
    }

    // Free the device array
    acc_free(dev_array);

    // Free the host array
    free(host_array);

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