#include "acc_testsuite.h"
#include <stdlib.h>

//T1:shutdown directive, V:2.7-3.0
int test1(){
    int err = 0;
    
    // Initializing device
    #pragma acc init 
    int device_count = acc_get_num_devices(acc_get_device_type());
      
    if(device_count > 0) {
        // Shutdown a specific device. Assuming device 0 is available
        #pragma acc shutdown device_num(0)
    } else {
        err = 1; // No device available.
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    int NUM_TEST_CALLS = 5;
  
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}