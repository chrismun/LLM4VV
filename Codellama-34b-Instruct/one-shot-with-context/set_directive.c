#include <openacc.h>

int main() {
    int async_var = acc_async_default;
    int device_num = 0;
    int device_type = acc_device_type_default;

    // Set the default asynchronous queue to acc_async_default
    #pragma acc set default_async(acc_async_default)

    // Set the device number to 0
    #pragma acc set device_num(0)

    // Set the device type to acc_device_type_default
    #pragma acc set device_type(acc_device_type_default)

    // Conditionally set the default asynchronous queue to acc_async_sync
    #pragma acc set default_async(acc_async_sync) if (async_var == acc_async_default)

    // Conditionally set the device number to 1
    #pragma acc set device_num(1) if (device_num == 0)

    // Conditionally set the device type to acc_device_type_gpu
    #pragma acc set device_type(acc_device_type_gpu) if (device_type == acc_device_type_default)

    return 0;
}