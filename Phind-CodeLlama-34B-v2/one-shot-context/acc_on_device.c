#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;
    acc_device_t device_type = acc_get_device_type();

    // Check if the device type is GPU
    if (acc_on_device(device_type) == 1) {
        printf("The code is running on a GPU device.\n");
    } else {
        printf("The code is not running on a GPU device.\n");
        err = 1;
    }

    // Check if the device type is not a GPU
    if (acc_on_device(acc_device_not_host) == 1) {
        printf("The code is running on a non-GPU device.\n");
    } else {
        printf("The code is not running on a non-GPU device.\n");
        err = 1;
    }

    // Check if the device type is host
    if (acc_on_device(acc_device_host) == 1) {
        printf("The code is running on the host.\n");
    } else {
        printf("The code is not running on the host.\n");
        err = 1;
    }

    return err;
}