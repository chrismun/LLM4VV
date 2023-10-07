#include "acc_testsuite.h"

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Create a shared memory region
    int *shared_mem = (int *)acc_malloc(sizeof(int));

    // Create a device memory region
    int *device_mem = (int *)acc_malloc(sizeof(int));

    // Initialize the shared memory region
    *shared_mem = 1;

    // Initialize the device memory region
    *device_mem = 2;

    // Create a compute construct with the no_create clause
    #pragma acc parallel num_gangs(1) no_create(shared_mem)
    {
        // Increment the shared memory region
        *shared_mem += 1;

        // Attach the device memory region to the shared memory region
        acc_attach(device_mem, shared_mem);

        // Increment the device memory region
        *device_mem += 1;

        // Detach the device memory region from the shared memory region
        acc_detach(device_mem, shared_mem);
    }

    // Check the values of the shared and device memory regions
    if (*shared_mem != 2 || *device_mem != 3) {
        err = 1;
    }

    // Free the memory regions
    acc_free(shared_mem);
    acc_free(device_mem);

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