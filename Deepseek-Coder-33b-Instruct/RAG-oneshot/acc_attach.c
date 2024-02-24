#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int *host_ptr, *device_ptr;
    int size = sizeof(int);

    // Allocate memory on the host
    host_ptr = (int*)malloc(size);
    *host_ptr = 10;

    // Allocate memory on the device
    device_ptr = (int*)acc_malloc(size);

    // Attach the device pointer to the host pointer
    acc_attach((void**)&device_ptr);

    // Copy data from the host to the device
    acc_memcpy_to_device(device_ptr, host_ptr, size);

    // Detach the device pointer from the host pointer
    acc_detach((void**)&device_ptr);

    // Free the memory
    free(host_ptr);
    acc_free(device_ptr);

    return 0;
}