#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a reference counter
    acc_reference_counter_t ref_counter;
    acc_reference_counter_init(&ref_counter);

    // Increment the reference counter
    acc_reference_counter_increment(&ref_counter);

    // Decrement the reference counter
    acc_reference_counter_decrement(&ref_counter);

    // Check if the reference counter is zero
    if (acc_reference_counter_is_zero(&ref_counter)) {
        // Reference counter is zero, return 1
        err = 1;
    }

    // Clean up the reference counter
    acc_reference_counter_destroy(&ref_counter);

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