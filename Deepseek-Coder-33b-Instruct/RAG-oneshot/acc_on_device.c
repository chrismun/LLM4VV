#include <stdio.h>
#include <openacc.h>

int main() {
    acc_device_t dev_type = acc_device_host;

    if (acc_on_device(dev_type)) {
        printf("The code is running on the host.\n");
    } else {
        printf("The code is not running on the host.\n");
    }

    dev_type = acc_device_nvidia;
    if (acc_on_device(dev_type)) {
        printf("The code is running on a NVIDIA device.\n");
    } else {
        printf("The code is not running on a NVIDIA device.\n");
    }

    return 0;
}