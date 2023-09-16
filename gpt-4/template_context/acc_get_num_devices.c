#include "acc_testsuite.h"
#include <openacc.h>
#ifndef T1
//T1:acc get num devices,V:2.7-3.3
int test1(){
    int err = 0;

    // Call acc_get_num_devices with acc_device_default as parameter
    int num_devices = acc_get_num_devices(acc_device_default);

    // Check if the number of devices is non-negative
    if(num_devices < 0){
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