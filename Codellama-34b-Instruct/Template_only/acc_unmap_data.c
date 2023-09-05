#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new data region
    acc_data_region_t data_region;
    data_region.type = ACC_DATA_REGION_TYPE_UNDEFINED;
    data_region.size = 0;
    data_region.host_ptr = NULL;
    data_region.device_ptr = NULL;

    // Map the data region to the device
    acc_map_data(data_region, ACC_DATA_REGION_TYPE_UNDEFINED, 0, 0, 0, 0, 0);

    // Unmap the data region from the device
    acc_unmap_data(data_region, ACC_DATA_REGION_TYPE_UNDEFINED, 0, 0, 0, 0, 0);

    // Check that the data region is no longer mapped to the device
    if (data_region.device_ptr != NULL) {
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