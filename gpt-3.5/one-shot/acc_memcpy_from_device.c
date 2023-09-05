#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

void validate_result(float* data) {
    for (int i = 0; i < N; i++) {
        printf("%f ", data[i]);
    }
}

int main() {
    float* host_data = (float*) malloc(N * sizeof(float));
    float* device_data = (float*) acc_malloc(N * sizeof(float));

    // Initialize data on host
    for (int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Transfer data from host to device
    acc_memcpy_to_device(device_data, host_data, N * sizeof(float));

    // Transfer data from device to host
    acc_memcpy_from_device(host_data, device_data, N * sizeof(float));

    // Validate result
    validate_result(host_data);

    // Free allocated memory
    free(host_data);
    acc_free(device_data);

    return 0;