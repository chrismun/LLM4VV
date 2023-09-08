#include "acc_testsuite.h"
#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *host_ptr = (int *)malloc(sizeof(int));
    int *device_ptr = (int *)malloc(sizeof(int));

    // Set the host pointer to a value
    *host_ptr = 1234;

    // Use the data deviceptr clause to declare the device pointer
    #pragma acc data deviceptr(device_ptr)
    {
        // Copy the value from the host pointer to the device pointer
        device_ptr = host_ptr;
    }

    // Check that the value was copied correctly
    if (*device_ptr != *host_ptr) {
        err = 1;
    }

    // Free the memory
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