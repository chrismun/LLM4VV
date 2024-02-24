#include <stdio.h>
#include <openacc.h>

int main() {
    int device_type = acc_get_device_type();
    if (device_type == acc_device_host) {
        printf("Device type is host\n");
    } else if (device_type == acc_device_not_host) {
        printf("Device type is not host\n");
    } else if (device_type == acc_device_nvidia) {
        printf("Device type is NVIDIA\n");
    } else if (device_type == acc_device_radeon) {
        printf("Device type is AMD\n");
    } else if (device_type == acc_device_xeonphi) {
        printf("Device type is Xeon Phi\n");
    } else {
        printf("Unknown device type\n");
    }

    return 0;
}