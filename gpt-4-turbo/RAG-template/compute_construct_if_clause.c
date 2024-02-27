#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test variables
    int host_array[128];
    int device_array[128];
    int condition_true = 1; // Condition that will always evaluate to true
    int condition_false = 0; // Condition that will always evaluate to false
    int i;

    // Initialize host array with random data
    for (i = 0; i < 128; ++i){
        host_array[i] = rand() / (RAND_MAX / 100);
    }

    // Copy data to device and compute with 'if' clause evaluating to true
    #pragma acc data copy(device_array)
    {
        #pragma acc parallel loop if(condition_true)
        for (i = 0; i < 128; ++i){
            device_array[i] = host_array[i] + 1;
        }
    }

    // Validate that the computation was done on the device
    for (i = 0; i < 128; ++i){
        if (device_array[i] != host_array[i] + 1){
            err += 1;
        }
    }

    // Reset device_array for next test
    for (i = 0; i < 128; ++i){
        device_array[i] = 0;
    }

    // Copy data to device and compute with 'if' clause evaluating to false
    #pragma acc data copy(device_array)
    {
        #pragma acc parallel loop if(condition_false)
        for (i = 0; i < 128; ++i){
            device_array[i] = host_array[i] + 1;
        }
    }

    // Validate that the computation was done by the local thread (no change to device_array expected as it should skip device execution)
    for (i = 0; i < 128; ++i){
        if (device_array[i] != 0){ // Checking for unchanged device_array values
            err += 1;
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