#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data construct with a single data region
    acc_data_construct_t data_construct;
    data_construct.type = ACC_DATA_CONSTRUCT_TYPE_DATA;
    data_construct.data_region = ACC_DATA_REGION_TYPE_HOST;
    data_construct.data_region_size = 1;
    data_construct.data_region_ptr = (void*)&data;
    data_construct.data_region_ptr_size = sizeof(data);

    // Attach the data construct to the current device
    acc_attach_data_construct(&data_construct);

    // Verify that the data construct is attached to the current device
    if (acc_get_data_construct_device(&data_construct) != acc_get_current_device()) {
        err = 1;
    }

    // Detach the data construct from the current device
    acc_detach_data_construct(&data_construct);

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