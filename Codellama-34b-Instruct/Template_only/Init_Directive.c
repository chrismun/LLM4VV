#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize a random value
    int value = rand();

    // Create a new data region
    acc_region_t region = acc_create_region(value);

    // Initialize the data region
    acc_init_region(region);

    // Check that the data region is initialized
    if (acc_is_region_initialized(region) == 0) {
        err = 1;
    }

    // Destroy the data region
    acc_destroy_region(region);

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