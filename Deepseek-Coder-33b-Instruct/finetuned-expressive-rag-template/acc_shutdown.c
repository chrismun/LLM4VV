#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Get the number of devices
    int num_devices = acc_get_num_devices(acc_device_nvidia);

    // Shutdown all devices
    for(int i = 0; i < num_devices; i++){
        acc_shutdown(acc_device_nvidia);
    }

    // Check if all devices are shut down
    if(acc_get_num_devices(acc_device_nvidia) != 0){
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