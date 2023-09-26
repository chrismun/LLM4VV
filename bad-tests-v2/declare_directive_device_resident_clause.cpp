#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable in device memory
    int* device_var;
    device_var = (int*)acc_malloc(sizeof(int));

    // Set the value of the variable in device memory
    *device_var = 123;

    // Declare a variable in host memory
    int* host_var;
    host_var = (int*)malloc(sizeof(int));

    // Set the value of the variable in host memory
    *host_var = 456;

    // Use the device_resident clause to specify that the variable in device memory should be used
    acc_device_resident(device_var);

    // Use the device_resident clause to specify that the variable in host memory should be used
    acc_device_resident(host_var);

    // Check that the value of the variable in device memory is correct
    if (*device_var != 123){
        err = 1;
    }

    // Check that the value of the variable in host memory is correct
    if (*host_var != 456){
        err = 1;
    }

    // Free the memory allocated for the variables
    acc_free(device_var);
    free(host_var);

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