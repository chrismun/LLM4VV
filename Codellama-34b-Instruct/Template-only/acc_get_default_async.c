#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async mode to async
    acc_set_default_async(ACC_ASYNC);

    // Create a data region with the default async mode
    acc_data_region_t data_region = acc_create_data_region(ACC_DEFAULT_ASYNC);

    // Verify that the data region is created with the default async mode
    if (data_region->async != ACC_ASYNC) {
        err = 1;
    }

    // Clean up the data region
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