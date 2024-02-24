#include <iostream>
#include <openacc.h>

int main() {
    int err = 0;

    // Set the default async queue to acc_async_sync
    #pragma acc set default_async(acc_async_sync)

    // Check if the default async queue is set to acc_async_sync
    if (acc_get_default_async() != acc_async_sync) {
        err = 1;
    }

    // Set the default device number to 0
    #pragma acc set device_num(0)

    // Check if the default device number is set to 0
    if (acc_get_device_num(acc_device_not_host) != 0) {
        err = 1;
    }

    // Set the default device type to acc_device_nvidia
    #pragma acc set device_type(acc_device_nvidia)

    // Check if the default device type is set to acc_device_nvidia
    if (acc_get_device_type() != acc_device_nvidia) {
        err = 1;
    }

    return err;
}