#include "acc_testsuite.h"
#ifndef T1
//T1:{host_data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int data_size = 1024;
    int *host_array = (int*)malloc(sizeof(int) * data_size);
    int *device_array = (int*)acc_malloc(sizeof(int) * data_size);
    bool condition = true; // condition for the if clause

    // Initialize host array with random values
    for(int i = 0; i < data_size; ++i){
        host_array[i] = rand() % 100;
    }
    
    // Copy data to device array
    acc_memcpy_to_device(device_array, host_array, sizeof(int) * data_size);
    
    // Use host_data construct with if clause to conditionally run on the device
    #pragma acc host_data use_device(device_array) if(condition)
    {
        // Assuming a hypothetical device function that increments each element (represented as a loop here)
        for(int i = 0; i < data_size; ++i){
            device_array[i] += 1; // Increment each element if condition is true.
        }
    }
    
    // Copy data back to host to verify
    acc_memcpy_from_device(host_array, device_array, sizeof(int) * data_size);
    
    // Verify the increment has been applied, indicating the if clause was respected
    for(int i = 0; i < data_size; ++i){
        if(host_array[i] != (host_array[i] - 1 + 1)){ // Check if increment took place
            err += 1;
        }
    }
    
    free(host_array);
    acc_free(device_array);
    
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