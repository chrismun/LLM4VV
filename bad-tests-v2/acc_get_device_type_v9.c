#include <openacc.h>

acc_device_t acc_get_device_type(void) {
    acc_device_t device_type;
    int device_id;

    device_id = acc_get_device();
    if (device_id == acc_device_none) {
        return acc_device_none;
    }

    device_type = acc_get_device_type_from_id(device_id);
    if (device_type == acc_device_none) {
        return acc_device_none;
    }

    return device_type;
}