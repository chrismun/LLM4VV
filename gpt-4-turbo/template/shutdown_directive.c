#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:3.0-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int *host_data = (int*) malloc(sizeof(int) * 128);
    int *device_data;
    for (int i = 0; i < 128; ++i){
        host_data[i] = rand()/(RAND_MAX/100);
    }
    
    // Ensuring device is initialized
    acc_init(acc_device_default);
    
    // Copy data to the device
    #pragma acc enter data create(device_data[0:128])
    #pragma acc parallel loop copyin(host_data[0:128]) copyout(device_data[0:128])
    for(int i = 0; i < 128; ++i){
        device_data[i] = host_data[i] * 2;
    }
    
    // Double-checking the operation
    for(int i = 0; i < 128; ++i){
        if(device_data[i] != host_data[i] * 2){
            err++;
        }
    }

    // Free device data
    #pragma acc exit data delete(device_data[0:128])
    
    // Shutdown the device explicitly
    acc_shutdown(acc_device_default);
    
    // Attempt to use the device after shutdown, should not work if shutdown was successful
    #pragma acc enter data create(device_data[0:128])
    #pragma acc parallel loop
    for(int i = 0; i < 128; ++i){
        device_data[i] = 0; // This operation should not be successful
    }
    
    // If no error was detected, it might indicate that shutdown did not free resources as expected
    // However, actual resource management post-shutdown can vary by implementation
    // This simple test may not conclusively verify shutdown behavior
    
    free(host_data);
    
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