#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the attachment counter for the pointer
    int attachment_counter = 0;

    // Allocate a pointer in device memory
    int* ptr = (int*)acc_malloc(sizeof(int));

    // Attach the pointer to a device address
    acc_attach(ptr, sizeof(int), 0);

    // Increment the attachment counter
    attachment_counter++;

    // Detach the pointer from the device address
    acc_detach(ptr);

    // Decrement the attachment counter
    attachment_counter--;

    // Check if the attachment counter is zero
    if (attachment_counter == 0) {
        // The pointer is detached, so we can free the memory
        acc_free(ptr);
    } else {
        // The pointer is still attached, so we cannot free the memory
        err = 1;
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