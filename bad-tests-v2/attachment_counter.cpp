#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int* dev_ptr = (int*)acc_malloc(sizeof(int));

    // Set the attachment counter to 0
    acc_attach_counter(dev_ptr, 0);

    // Attach the pointer to a target address
    int* target_ptr = (int*)acc_malloc(sizeof(int));
    acc_attach(dev_ptr, target_ptr, sizeof(int));

    // Increment the attachment counter
    acc_attach_counter(dev_ptr, 1);

    // Detach the pointer from the target address
    acc_detach(dev_ptr);

    // Decrement the attachment counter
    acc_attach_counter(dev_ptr, -1);

    // Check that the attachment counter is 0
    assert(acc_attach_counter(dev_ptr) == 0);

    // Free the device memory
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