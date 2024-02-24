#include <stdio.h>
#include <openacc.h>

int main() {
    acc_init(acc_device_host); // Initialize the device

    printf("Device initialized\n");

    // Perform some computations on the device
    // ...

    // Shutdown the device
    acc_shutdown(acc_device_host);

    printf("Device shutdown\n");

    return 0;
}