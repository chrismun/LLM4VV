#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t dev_type = acc_get_device_type();

    switch (dev_type) {
        case acc_device_default:
            printf("Default device type\n");
            break;
        case acc_device_nvidia:
            printf("NVIDIA GPU\n");
            break;
        case acc_device_radeon:
            printf("AMD GPU\n");
            break;
        case acc_device_xeonphi:
            printf("Intel Xeon Phi\n");
            break;
        case acc_device_host:
            printf("Host\n");
            break;
        default:
            printf("Unknown device type\n");
            break;
    }

    return 0;
}