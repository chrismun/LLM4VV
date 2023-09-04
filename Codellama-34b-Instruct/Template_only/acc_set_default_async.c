#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async value to 1
    acc_set_default_async(1);

    // Create a data region with the default async value
    acc_data_region_t data_region = acc_create_data_region(acc_default_async);

    // Create a data object with the default async value
    acc_data_t data = acc_create_data(data_region, acc_default_async);

    // Set the data object to a random value
    acc_set_data(data, acc_default_async, rand());

    // Check that the data object has the correct value
    if (acc_get_data(data, acc_default_async) != rand()) {
        err = 1;
    }

    // Destroy the data object and data region
    acc_destroy_data(data);
    acc_destroy_data_region(data_region);

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