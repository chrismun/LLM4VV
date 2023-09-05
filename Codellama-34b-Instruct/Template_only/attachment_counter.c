#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new attachment counter
    acc_attach_counter(0, 0, 0, 0, 0);

    // Increment the attachment counter
    acc_attach_counter(0, 0, 0, 0, 1);

    // Check if the attachment counter is equal to 1
    if (acc_attach_counter(0, 0, 0, 0, 0) != 1) {
        err = 1;
    }

    // Decrement the attachment counter
    acc_attach_counter(0, 0, 0, 0, -1);

    // Check if the attachment counter is equal to 0
    if (acc_attach_counter(0, 0, 0, 0, 0) != 0) {
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