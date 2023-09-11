#include "acc_testsuite.h"

#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* data = (int*)malloc(sizeof(int) * 10);
    int* data_present = (int*)malloc(sizeof(int) * 10);

    // Initialize data and data_present
    for (int i = 0; i < 10; i++) {
        data[i] = i;
        data_present[i] = 0;
    }

    // Attach data to the device
    acc_attach(data, sizeof(int) * 10);

    // Increment the structured reference counter for data
    acc_present_increment(data, sizeof(int) * 10);

    // Detach data from the device
    acc_detach(data, sizeof(int) * 10);

    // Decrement the structured reference counter for data
    acc_present_decrement(data, sizeof(int) * 10);

    // Check if the structured reference counter is zero
    if (acc_present_get_reference_count(data) == 0) {
        // Delete data
        free(data);
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