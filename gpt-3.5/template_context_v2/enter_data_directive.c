#include "acc_testsuite.h"
#ifndef T1
// T1: enter data directive, V: 2.7-3.3
int test1(){
    int err = 0;
    
    // Initialize host array
    int size = 10;
    int host_arr[size];
    for(int i=0; i<size; i++){
        host_arr[i] = i;
    }
    
    // Declare and allocate device array
    int* device_arr = (int*)acc_malloc(size * sizeof(int));
    
    // Transfer data from host to device
    #pragma acc enter data copyin(host_arr[0:size])
    
    // Verify data transfer
    #pragma acc parallel loop
    for(int i=0; i<size; i++){
        if(device_arr[i] != host_arr[i]){
            err = 1;
            break;
        }
    }
    
    // Free device memory
    acc_free(device_arr);
    
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