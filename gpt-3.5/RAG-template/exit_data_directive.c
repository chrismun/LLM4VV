#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    
    int *host_ptr, *device_ptr;
    int size = 10;

    host_ptr = (int*)malloc(size * sizeof(int));
    device_ptr = (int*)malloc(size * sizeof(int));

    // Initialize host data
    for(int i = 0; i < size; i++)
        host_ptr[i] = rand() % 100;

    #pragma acc enter data create(device_ptr[0:size]) // Create device data
    
    #pragma acc data copyin(host_ptr[0:size]) // Copy host data to device
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; i++)
            device_ptr[i] = host_ptr[i];

        #pragma acc exit data delete(device_ptr[0:size]) // Delete device data
    }

    // Check if device data is cleared
    for(int i = 0; i < size; i++){
        if(device_ptr[i] != 0){
            err = 1;
            break;
        }
    }

    free(host_ptr);
    free(device_ptr);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}