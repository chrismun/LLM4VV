#include "acc_testsuite.h"

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate space in the current device memory
    d_void* ptr = acc_malloc(1024);
    if (ptr == NULL) {
        // Allocation error
        err = 1;
    } else {
        // Use the deviceptr clause to tell the compiler that the pointer target is resident on the device
        #pragma acc deviceptr(ptr)

        // Use the pointer to access the device memory
        // ...

        // Free the memory when it is no longer needed
        acc_free(ptr);
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