#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Allocate memory on the device
    #pragma acc enter data create(device_data[0:N])

    // Copy data to the device
    #pragma acc update device(device_data[0:N])

    // Delete data from the device
    #pragma acc delete(device_data[0:N])

    // Check if the data is still present in the device memory
    int is_present = acc_is_present(device_data, N * sizeof(int));

    // Free the host memory
    free(data);

    // If the data is present, return 1, otherwise return 0
    return is_present ? 1 : 0;
}