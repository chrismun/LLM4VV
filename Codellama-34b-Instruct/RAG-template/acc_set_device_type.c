#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_GPU);

    // Create a compute region that uses the GPU device
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        // Do some computation on the GPU
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 100; i++) {
            // Do some computation
        }
    }

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_CPU);

    // Create a compute region that uses the CPU device
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        // Do some computation on the CPU
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 100; i++) {
            // Do some computation
        }
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