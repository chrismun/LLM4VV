#include "acc_testsuite.h"

#ifndef T1
//T1:acc create,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate memory on the device
    void *dev_ptr = acc_create(NULL, 1024);
    if (dev_ptr == NULL) {
        err = 1;
    }

    // Check if the memory is correctly allocated
    if (acc_is_present(dev_ptr, 1024) != 1) {
        err = 1;
    }

    // Free the memory
    acc_free(dev_ptr);

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