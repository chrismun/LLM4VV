#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;

    // Get the device type and number
    int dev_type = acc_get_device_type();
    int dev_num = acc_get_device_number();

    // Get the memory size and free memory size for the device
    size_t mem_size = acc_get_property(dev_num, dev_type, acc_property_memory);
    size_t free_mem_size = acc_get_property(dev_num, dev_type, acc_property_free_memory);

    // Check that the memory size is greater than the free memory size
    if (mem_size <= free_mem_size) {
        err = 1;
    }

    // Get the device name, vendor, and driver version
    const char* name = acc_get_property_string(dev_num, dev_type, acc_property_name);
    const char* vendor = acc_get_property_string(dev_num, dev_type, acc_property_vendor);
    const char* driver_version = acc_get_property_string(dev_num, dev_type, acc_property_driver);

    // Check that the device name, vendor, and driver version are not empty
    if (name == NULL || vendor == NULL || driver_version == NULL) {
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