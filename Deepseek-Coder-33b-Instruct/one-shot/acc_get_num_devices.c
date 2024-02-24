#include <stdio.h>
#include <openacc.h>

int main() {
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    printf("Number of NVIDIA devices: %d\n", num_devices);

    num_devices = acc_get_num_devices(acc_device_radeon);
    printf("Number of AMD/ATI devices: %d\n", num_devices);

    num_devices = acc_get_num_devices(acc_device_xeonphi);
    printf("Number of Intel Xeon Phi devices: %d\n", num_devices);

    num_devices = acc_get_num_devices(acc_device_default);
    printf("Number of default devices: %d\n", num_devices);

    return 0;
}