#include <stdio.h>
#include <openacc.h>

int main() {

    acc_init(acc_device_default);

    acc_set_device_type(acc_device_gpu);
    
    if (acc_get_device_type() == acc_device_gpu) {
        printf("acc_set_device_type successfully set the device type to GPU.\n");
    }
    else {
        printf("acc_set_device_type failed to set the device type to GPU.\n");
    }

    acc_shutdown(acc_device_default);

    return 0;