#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_default);
    int num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices < 1) {
        printf("Error: No acc_device_default available.\n");
        return ++err;
    }
    acc_set_device_type(acc_device_default);
    acc_device_t dev_type = acc_get_device_type();
    
    // Let's query for a property - number of compute units (if supported) or any available property
    // NOTE: ACC_DEVICE_NUM_CORES is a fictitious property for illustrative purposes. Please check the OpenACC specification for actual properties.
    int property_value = acc_get_property(0, dev_type, ACC_DEVICE_NUM_CORES); 
    if (property_value <= 0) {
        printf("Error: Failed to retrieve a valid property value for ACC_DEVICE_NUM_CORES.\n");
        ++err;
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