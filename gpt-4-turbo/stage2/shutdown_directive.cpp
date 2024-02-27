#include <stdlib.h>
#include "acc_testsuite.h"
#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Assuming a simple mechanism to check if devices are available before shutdown
    int num_devices = acc_get_num_devices(acc_device_none); // acc_device_none to query all types
    if (num_devices == 0) {
        // If no devices are available, that would be an environment error, not a directive error
        return 0;
    }

    #pragma acc enter data copyin(err)
    // Perform an operation on the devices to ensure they are active
    #pragma acc parallel num_gangs(1)
    {
        // Dummy operation to ensure device activity
        err += 0;
    }

    // Shutdown directive with condition (using a trivially true condition for simplicity)
    bool condition = true; // This could be dynamic based on the actual usage scenario
    #pragma acc shutdown if(condition)

    int err_after_shutdown = 0;
    // Attempt to perform an operation after shutdown, expecting it not to execute
    #pragma acc parallel num_gangs(1) reduction(+:err_after_shutdown)
    {
        err_after_shutdown = 1; // Should not be executed if shutdown was successful
    }

    // Exit data region, should have no effect as the device is shut down
    #pragma acc exit data copyout(err)

    if (condition && (err_after_shutdown != 0)) {
        err = 1; // If the operation was executed after shutdown, it's an error
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