#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_nvidia); // Initialize OpenACC on NVIDIA device

    // Check if OpenACC is supported
    if (acc_get_num_devices(acc_device_nvidia) == 0) {
        printf("OpenACC is not supported on this device.\n");
        return 1;
    }

    printf("OpenACC is supported on this device.\n");
    return 0;
}