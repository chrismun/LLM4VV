#include "acc_testsuite.h"

#ifndef T1
//T1:reference counters,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int* device_data = (int*)acc_malloc(sizeof(int));

    // Set the initial value of the structured reference counter
    acc_set_structured_reference_counter(device_data, 1);

    // Set the initial value of the dynamic reference counter
    acc_set_dynamic_reference_counter(device_data, 0);

    // Increment the structured reference counter
    acc_increment_structured_reference_counter(device_data);

    // Increment the dynamic reference counter
    acc_increment_dynamic_reference_counter(device_data);

    // Decrement the dynamic reference counter
    acc_decrement_dynamic_reference_counter(device_data);

    // Check if the reference counters are zero
    if (acc_get_structured_reference_counter(device_data) == 0 &&
        acc_get_dynamic_reference_counter(device_data) == 0) {
        // Reference counters are zero, data lifetime in device memory has ended
        err = 1;
    }

    // Free the device memory region
    acc_free(device_data);

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