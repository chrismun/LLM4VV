#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data = NULL;

    // Allocate memory on the device
    device_data = (int*)acc_malloc(N * sizeof(int));

    // Copy data from host to device
    acc_memcpy_to_device(device_data, host_data, N * sizeof(int));

    // Free device memory
    acc_free(device_data);

    // Free host memory
    free(host_data);

    return 0;
}