#include "openacc.h"
#include "acc_testsuite.h"
#include <stdio.h>

int main() {
    int failcode = 0;
    acc_device_t device_type;

    /* Test acc_init for various device types */
    device_type = acc_device_host;
    acc_init(device_type);
    if (acc_get_device_type() != device_type) {
        printf("Failed to initialize host device\n");
        failcode |= 1;
    }

    device_type = acc_device_not_host;
    acc_init(device_type);
    if (acc_get_device_type() != device_type) {
        printf("Failed to initialize non-host device\n");
        failcode |= 2;
    }

    device_type = acc_device_default;
    acc_init(device_type);
    if (acc_get_device_type() != device_type) {
        printf("Failed to initialize default device\n");
        failcode |= 4;
    }

    device_type = acc_device_gpu;
    acc_init(device_type);
    if (acc_get_device_type() != device_type) {
        printf("Failed to initialize GPU device\n");
        failcode |= 8;
    }

    device_type = acc_device_xeonphi;
    acc_init(device_type);
    if (acc_get_device_type() != device_type) {
        printf("Failed to initialize Xeon Phi device\n");
        failcode |= 16;
    }

    return failcode;
}