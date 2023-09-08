#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;

    // allocate a pointer in device memory
    int* ptr = (int*)acc_malloc(sizeof(int));

    // attach the pointer to a device address
    acc_attach(ptr, sizeof(int));

    // increment the attachment counter
    acc_attach(ptr, sizeof(int));

    // detach the pointer from the device address
    acc_detach(ptr);

    // decrement the attachment counter
    acc_detach(ptr);

    // check if the attachment counter is zero
    if (acc_get_attachment_counter(ptr) != 0) {
        err = 1;
    }

    // free the pointer
    acc_free(ptr);

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