#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;

    // declare a variable on the device
    int *device_var;
    device_var = (int *)acc_malloc(sizeof(int));

    // set the value of the variable on the device
    *device_var = 42;

    // declare a variable on the host
    int host_var;

    // copy the value of the device variable to the host variable
    host_var = *device_var;

    // check that the value of the host variable is the same as the value of the device variable
    if (host_var != 42) {
        err = 1;
    }

    // free the memory allocated on the device
    acc_free(device_var);

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