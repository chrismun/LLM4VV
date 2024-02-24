#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_ptr = (int*)malloc(N * sizeof(int));
    int *device_ptr;

    // Initialize host_ptr
    for(int i = 0; i < N; i++) {
        host_ptr[i] = i;
    }

    // Allocate device memory
    device_ptr = (int*)acc_malloc(N * sizeof(int));

    // Attach host_ptr to device_ptr
    acc_attach((void**)&device_ptr);

    // Copy data from host_ptr to device_ptr
    acc_memcpy_to_device(device_ptr, host_ptr, N * sizeof(int));

    // Detach device_ptr from host_ptr
    acc_detach((void**)&device_ptr);

    // Free device memory
    acc_free(device_ptr);

    // Free host memory
    free(host_ptr);

    return 0;
}