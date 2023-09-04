#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_runtime.h>

int acc_get_device_type(void) {
    int device_type = acc_get_device_type_var();
    if (device_type == acc_device_none) {
        return acc_device_none;
    }
    return device_type;
}

int main() {
    int device_type = acc_get_device_type();
    if (device_type == acc_device_none) {
        printf("Device type not set\n");
    } else {
        printf("Device type: %s\n", acc_device_type_to_string(device_type));
    }
    return 0;
}