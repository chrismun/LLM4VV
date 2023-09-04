#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

int acc_get_property(int dev_num, acc_device_t dev_type, acc_device_property_t property) {
    int err = 0;
    size_t value;

    switch (property) {
    case acc_property_memory:
        value = acc_get_memory_size(dev_num, dev_type);
        break;
    case acc_property_free_memory:
        value = acc_get_free_memory_size(dev_num, dev_type);
        break;
    case acc_property_shared_memory_support:
        value = acc_get_shared_memory_support(dev_num, dev_type);
        break;
    case acc_property_name:
        value = acc_get_device_name(dev_num, dev_type);
        break;
    case acc_property_vendor:
        value = acc_get_device_vendor(dev_num, dev_type);
        break;
    case acc_property_driver:
        value = acc_get_device_driver(dev_num, dev_type);
        break;
    default:
        err = 1;
        break;
    }

    if (err) {
        fprintf(stderr, "Error: Unsupported property %d\n", property);
        return 1;
    }

    return value;
}

int main() {
    int dev_num = 0;
    acc_device_t dev_type = acc_device_default;
    acc_device_property_t property = acc_property_memory;

    int value = acc_get_property(dev_num, dev_type, property);

    if (value == 0) {
        printf("Device %d has %d bytes of memory\n", dev_num, value);
    } else {
        printf("Error: Device %d does not support property %d\n", dev_num, property);
    }

    return 0;
}