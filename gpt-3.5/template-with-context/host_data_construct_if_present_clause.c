#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int host_var = 0;
    int* device_ptr = NULL;
    srand(SEED);

    // Allocating memory on the device
    #pragma acc enter data create(device_ptr[:1])
    
    // If the device supports the 'host_data' construct, the 'if_present' clause will ensure that the device_ptr is present in the current device memory.
    // If the device does not support the 'host_data' construct, the 'if_present' clause will have no effect.
    // The 'host_data' construct transfers the host variable 'host_var' to the device memory.
    #pragma acc host_data use_device(device_ptr[:1]) if_present(host_var) // Modify this line to test the if_present clause
    {
        // Using host_var on the host
        host_var = rand() % 100;
        
        // Accessing device_ptr on the device
        device_ptr[0] = host_var;
    }

    // Freeing memory on the device
    #pragma acc exit data delete(device_ptr[:1])

    // Verifying the result
    if (device_ptr[0] != host_var){
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