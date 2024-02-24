#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t device_type = acc_get_device_type();

    switch (device_type) {
        case acc_device_none:
            printf("No device is currently active.\n");
            break;
        case acc_device_default:
            printf("The default device type is currently active.\n");
            break;
        case acc_device_host:
            printf("The host device is currently active.\n");
            break;
        case acc_device_not_host:
            printf("A device other than the host is currently active.\n");
            break;
        case acc_device_nvidia:
            printf("An NVIDIA GPU is currently active.\n");
            break;
        case acc_device_radeon:
            printf("An AMD GPU is currently active.\n");
            break;
        case acc_device_xeonphi:
            printf("An Intel Xeon Phi coprocessor is currently active.\n");
            break;
        case acc_device_gfx900:
            printf("A GFX900 GPU is currently active.\n");
            break;
        case acc_device_gfx906:
            printf("A GFX906 GPU is currently active.\n");
            break;
        case acc_device_fpga:
            printf("An FPGA is currently active.\n");
            break;
        case acc_device_any:
            printf("Any device is currently active.\n");
            break;
        default:
            printf("Unknown device type.\n");
            break;
    }

    return 0;
}