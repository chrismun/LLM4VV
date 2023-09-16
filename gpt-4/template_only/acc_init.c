#include "acc_testsuite.h"

#ifndef T1
//T1:acc init,V:3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the OpenACC runtime for a device of type acc_device_default
    acc_init(acc_device_default);

    // Check if it's in the device region to verify it was initialized correctly
    if(acc_get_device_type() != acc_device_default) {
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