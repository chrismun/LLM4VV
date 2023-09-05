#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t deviceType;
    deviceType = acc_get_device_type();

    switch (deviceType) {
        case acc_device_none:
            printf("Device Type: None\n");
            break;
        case acc_device_default:
            printf("Device Type: Default\n");
            break;
        case acc_device_host:
            printf("Device Type: Host\n");
            break;
        case acc_device_not_host:
            printf("Device Type: Not Host\n");
            break;
        case acc_device_nvidia:
            printf("Device Type: Nvidia GPU\n");
            break;
        case acc_device_radeon:
            printf("Device Type: Radeon GPU\n");
            break;
        case acc_device_intel:
            printf("Device Type: Intel GPU\n");
            break;
        case acc_device_custom:
            printf("Device Type: Custom Device\n");
            break;
        default:
            printf("Unknown Device Type\n");
            break;
    }

    return 0;