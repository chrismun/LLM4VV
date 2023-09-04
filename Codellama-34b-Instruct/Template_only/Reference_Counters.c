#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a reference counter
    acc_ref_counter_t counter;
    acc_ref_counter_init(&counter);

    // Increment the reference counter
    acc_ref_counter_inc(&counter);

    // Decrement the reference counter
    acc_ref_counter_dec(&counter);

    // Check if the reference counter is zero
    if (acc_ref_counter_is_zero(&counter)) {
        err = 1;
    }

    // Destroy the reference counter
    acc_ref_counter_destroy(&counter);

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