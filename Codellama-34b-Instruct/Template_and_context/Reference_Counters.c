#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a reference counter for the data
    int *ref_count = (int *)acc_malloc(sizeof(int));
    *ref_count = 0;

    // Create some data to be managed by the reference counter
    int *data = (int *)acc_malloc(sizeof(int));
    *data = 42;

    // Increment the reference counter when the data is created
    acc_increment_reference_count(ref_count, data);

    // Decrement the reference counter when the data is deleted
    acc_decrement_reference_count(ref_count, data);

    // Check that the reference counter is zero after the data is deleted
    if (*ref_count != 0) {
        err = 1;
    }

    // Free the reference counter and data
    acc_free(ref_count);
    acc_free(data);

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