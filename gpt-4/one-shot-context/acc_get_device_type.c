#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t devType = acc_get_device_type();

    switch(devType) {
        case acc_device_none:
            printf("Device type: None\n");
            break;
        case acc_device_default:
            printf("Device type: default\n");
            break;
        case acc_device_host:
            printf("Device type: host\n");
            break;
        case acc_device_not_host:
            printf("Device type: not host\n");
            break;
        case acc_device_nvidia:
            printf("Device type: NVIDIA\n");
            break;
        default:
            printf("Unknown device type\n");
    }

    return 0;
}