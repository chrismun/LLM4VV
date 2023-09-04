#include <stdlib.h>
#include <string.h>
#include <openacc.h>

size_t acc_get_property(int dev_num, acc_device_t dev_type, acc_device_property_t property) {
    size_t result = 0;
    switch (property) {
        case acc_property_memory:
            result = acc_get_memory_size(dev_num, dev_type);
            break;
        case acc_property_free_memory:
            result = acc_get_free_memory_size(dev_num, dev_type);
            break;
        case acc_property_shared_memory_support:
            result = acc_get_shared_memory_support(dev_num, dev_type);
            break;
        case acc_property_name:
            result = acc_get_device_name(dev_num, dev_type);
            break;
        case acc_property_vendor:
            result = acc_get_device_vendor(dev_num, dev_type);
            break;
        case acc_property_driver:
            result = acc_get_device_driver(dev_num, dev_type);
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

const char* acc_get_property_string(int dev_num, acc_device_t dev_type, acc_device_property_t property) {
    const char* result = NULL;
    switch (property) {
        case acc_property_memory:
            result = acc_get_memory_size_string(dev_num, dev_type);
            break;
        case acc_property_free_memory:
            result = acc_get_free_memory_size_string(dev_num, dev_type);
            break;
        case acc_property_shared_memory_support:
            result = acc_get_shared_memory_support_string(dev_num, dev_type);
            break;
        case acc_property_name:
            result = acc_get_device_name_string(dev_num, dev_type);
            break;
        case acc_property_vendor:
            result = acc_get_device_vendor_string(dev_num, dev_type);
            break;
        case acc_property_driver:
            result = acc_get_device_driver_string(dev_num, dev_type);
            break;
        default:
            result = NULL;
            break;
    }
    return result;
}