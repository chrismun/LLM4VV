#include "acc_testsuite.h"

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int* dev_ptr = (int*)acc_malloc(sizeof(int));
    if (dev_ptr == NULL) {
        err = 1;
        return err;
    }

    // Initialize the reference counters
    acc_set_reference_count(dev_ptr, 1);
    acc_set_dynamic_reference_count(dev_ptr, 0);

    // Enter a data region with an explicit data clause
    acc_data_enter_region(dev_ptr, sizeof(int), 0);

    // Increment the structured reference counter
    acc_set_reference_count(dev_ptr, 2);

    // Decrement the dynamic reference counter
    acc_set_dynamic_reference_count(dev_ptr, 1);

    // Exit the data region
    acc_data_exit_region(dev_ptr, sizeof(int), 0);

    // Check that the reference counters are correct
    if (acc_get_reference_count(dev_ptr) != 1 || acc_get_dynamic_reference_count(dev_ptr) != 0) {
        err = 1;
    }

    // Free the device memory region
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