#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // create a variable on the device
    int device_var;
    #pragma acc declare create(device_var)

    // check that the variable was created on the device
    #pragma acc kernels
    {
        device_var = 1;
    }

    // check that the variable was copied back to the host
    if (device_var != 1) {
        err++;
    }

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