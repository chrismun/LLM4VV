#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_num = 0;
    acc_device_t dev_type = acc_device_default;
    acc_device_property_t property;
    size_t property_value;
    const char* property_string_value;

    // Testing acc_property_memory
    property = acc_property_memory;
    property_value = acc_get_property(dev_num, dev_type, property);
    if (property_value == 0) {
        err = 1;
        acc_print_error("acc_get_property for acc_property_memory returned 0");
    }

    // Testing acc_property_free_memory
    property = acc_property_free_memory;
    property_value = acc_get_property(dev_num, dev_type, property);
    if (property_value == 0) {
        err = 1;
        acc_print_error("acc_get_property for acc_property_free_memory returned 0");
    }

    // Testing acc_property_shared_memory_support
    property = acc_property_shared_memory_support;
    property_value = acc_get_property(dev_num, dev_type, property);
    if (property_value == 0) {
        err = 1;
        acc_print_error("acc_get_property for acc_property_shared_memory_support returned 0");
    }

    // Testing acc_property_name
    property = acc_property_name;
    property_string_value = acc_get_property_string(dev_num, dev_type, property);
    if (property_string_value == NULL) {
        err = 1;
        acc_print_error("acc_get_property_string for acc_property_name returned NULL");
    }

    // Testing acc_property_vendor
    property = acc_property_vendor;
    property_string_value = acc_get_property_string(dev_num, dev_type, property);
    if (property_string_value == NULL) {
        err = 1;
        acc_print_error("acc_get_property_string for acc_property_vendor returned NULL");
    }

    // Testing acc_property_driver
    property = acc_property_driver;
    property_string_value = acc_get_property_string(dev_num, dev_type, property);
    if (property_string_value == NULL) {
        err = 1;
        acc_print_error("acc_get_property_string for acc_property_driver returned NULL");
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