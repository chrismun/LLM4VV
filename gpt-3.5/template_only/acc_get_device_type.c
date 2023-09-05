#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Call the acc_get_device_type function
    acc_device_t device_type = acc_get_device_type();

    // Verify the returned device type
    if (device_type != acc_device_not_host){
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
    
    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    
    // Check if any tests failed
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}