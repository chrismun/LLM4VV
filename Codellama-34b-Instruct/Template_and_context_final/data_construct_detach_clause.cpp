#include "acc_testsuite.h"

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    int* shared_mem = (int*)malloc(sizeof(int) * 10);

    // Initialize the shared memory region
    for (int i = 0; i < 10; i++) {
        shared_mem[i] = i;
    }

    // Create a detach clause
    acc_detach(shared_mem);

    // Check if the detach clause was successful
    if (acc_get_device_type() == acc_device_host) {
        // If the device is the host, the detach clause was not successful
        err = 1;
    }

    // Free the shared memory region
    free(shared_mem);

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