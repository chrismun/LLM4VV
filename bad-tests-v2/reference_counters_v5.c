#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a reference counter
    acc_ref_counter_t ref_counter;
    acc_ref_counter_init(&ref_counter);

    // Increment the reference counter
    acc_ref_counter_inc(&ref_counter);

    // Decrement the reference counter
    acc_ref_counter_dec(&ref_counter);

    // Check if the reference counter is zero
    if (acc_ref_counter_get(&ref_counter) == 0) {
        // The reference counter is zero, so the feature is not working properly
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