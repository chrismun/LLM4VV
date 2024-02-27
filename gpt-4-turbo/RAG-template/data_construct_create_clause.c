#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test initialization.
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    
    // Ensure the array starts uninitialized to detect if `create(zero)` works.
    for (int i = 0; i < size; ++i){
        a[i] = -1;
    }
    
    // Use OpenACC create clause to allocate memory on the device.
    // Also, test the 'zero' modifier by initializing the memory to zero.
    #pragma acc enter data create(a[0:size]) copyin(a[0:size])
    
    // Modify the values in the allocated array on the device.
    #pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i){
        a[i] = i * 2;
    }
    
    // Exit the data region, copying back the modified array to the host.
    #pragma acc exit data copyout(a[0:size])
    
    // Verify the modifications.
    for(int i = 0; i < size; ++i){
        if(a[i] != i * 2){
            err++;
        }
    }
    
    free(a);

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