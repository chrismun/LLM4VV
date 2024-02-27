#include "acc_testsuite.h"
#ifndef T1
//T1:{initialization},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Attempt to initialize OpenACC
    acc_init(acc_device_default);
    
    // After acc_init, check if any OpenACC devices are available.
    // The acc_get_num_devices function returns the number of available devices of a specific type.
    // If the number of devices for the default type is greater than 0, it indicates that 
    // OpenACC has been successfully initialized.
    if (acc_get_num_devices(acc_device_default) <= 0) {
        err = 1; // Record an error if no OpenACC devices are found.
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