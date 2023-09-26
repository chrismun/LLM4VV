#include "acc_testsuite.h"

#ifndef T1
//T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;

    // Initialize the runtime for the current device type
    #pragma acc init device_type(acc_device_current)

    // Check that the current device type is initialized
    if (acc_get_device_type() != acc_device_current) {
        err = 1;
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