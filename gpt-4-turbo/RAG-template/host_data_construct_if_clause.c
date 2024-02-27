#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int* host_ptr = (int*)malloc(sizeof(int));
    int* device_ptr = NULL;
    int original = rand();
    *host_ptr = original;
    
    // Dynamically decide to execute the host_data construct
    int execute_construct = rand() % 2;

    if (execute_construct) {
        #pragma acc enter data create(host_ptr[0:1])
        device_ptr = acc_deviceptr(host_ptr);
    }

    #pragma acc host_data if(execute_construct) use_device(device_ptr)
    {
        if (execute_construct) {
            // When the if condition is true, device_ptr should be valid and different.
            if (device_ptr == host_ptr) {
                err++;
            }
        }
    }

    if (execute_construct) {
        #pragma acc exit data delete(host_ptr[0:1])
    }
    
    // After exiting the data region, device_ptr should not be accessed.
    // However, the original pointer should still point to the same content.
    if (*host_ptr != original) {
        err++;
    }

    free(host_ptr);
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