#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *device_ptr = (int *)malloc(sizeof(int));
    if (device_ptr == NULL){
        err = 1;
    }

    // Set the device pointer to a value
    *device_ptr = 10;

    // Use the device pointer in an OpenACC kernel
    #pragma acc parallel present(device_ptr)
    {
        // Access the device pointer in the kernel
        int value = *device_ptr;
        if (value != 10){
            err = 1;
        }
    }

    // Free the device pointer
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