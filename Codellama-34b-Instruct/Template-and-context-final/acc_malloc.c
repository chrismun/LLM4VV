#include "acc_testsuite.h"

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate space in the current device memory
    d_void* device_ptr = acc_malloc(1024);

    // Use the device pointer in a deviceptr clause
    #pragma acc deviceptr(device_ptr)
    {
        // Do something with the device pointer
        // ...
    }

    // Free the device memory
    acc_free(device_ptr);

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