#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int *device_ptr;
    int *host_ptr;
    int size = sizeof(int);

    // Allocate memory on the device
    device_ptr = (int*)acc_malloc(size);

    // Initialize the device memory
    *device_ptr = 10;

    // Get the host pointer
    host_ptr = acc_hostptr(device_ptr);

    // Print the value of the host pointer
    printf("Value of the host pointer: %d\n", *host_ptr);

    // Free the device memory
    acc_free(device_ptr);

    return 0;
}