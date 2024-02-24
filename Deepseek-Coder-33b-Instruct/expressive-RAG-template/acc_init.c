#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;

    // Initialize the device
    acc_init(acc_device_host);

    // Check if the device was initialized correctly
    if (acc_get_device_type() != acc_device_host) {
        err = 1;
    }

    return err;
}