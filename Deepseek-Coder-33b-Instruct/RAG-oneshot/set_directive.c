#include <stdio.h>
#include <openacc.h>

int main() {
    // Set default async behavior
    #pragma acc set default_async(acc_async_sync)

    // Set device number
    #pragma acc set device_num(0)

    // Set device type
    #pragma acc set device_type(acc_device_nvidia)

    // Check the set directives
    int default_async = acc_get_default_async();
    int device_num = acc_get_device_num(acc_device_nvidia);
    int device_type = acc_get_device_type();

    printf("Default async behavior: %d\n", default_async);
    printf("Device number: %d\n", device_num);
    printf("Device type: %d\n", device_type);

    return 0;
}