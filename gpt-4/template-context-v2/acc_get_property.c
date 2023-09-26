#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    int property;
    acc_device_t acc_device_type = acc_device_nvidia;  // Change as per compiler type

    acc_set_device_type (acc_device_type);
    // Get the actual device
    acc_device_t actual_device = acc_get_device_type ();

    // Test: the actual device should be the same as the set device
    if (actual_device != acc_device_type){
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