#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;
    int device_type = acc_device_current;
    int device_num = acc_get_device_num(device_type);
    int async_default = acc_async_default;

    #pragma acc set device_type(device_type)
    #pragma acc set device_num(device_num)
    #pragma acc set default_async(async_default)

    if (acc_get_device_type() != device_type) {
        fprintf(stderr, "Error: Device type not set correctly.\n");
        err = 1;
    }

    if (acc_get_device_num(device_type) != device_num) {
        fprintf(stderr, "Error: Device number not set correctly.\n");
        err = 1;
    }

    if (acc_get_default_async() != async_default) {
        fprintf(stderr, "Error: Default async not set correctly.\n");
        err = 1;
    }

    return err;
}