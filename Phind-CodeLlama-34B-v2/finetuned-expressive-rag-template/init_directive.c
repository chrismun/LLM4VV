#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;

    // Initialize the device
    #pragma acc init device_type(acc_device_nvidia)

    // Check if the device is available
    if (acc_get_device_num(acc_device_nvidia) == acc_device_not_available) {
        fprintf(stderr, "No NVIDIA device available.\n");
        err = 1;
    }

    return err;
}