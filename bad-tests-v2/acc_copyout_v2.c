#include "acc_testsuite.h"
#include <assert.h>

#define SIZE 1000

// Define the test data
float host_data[SIZE];
float device_data[SIZE];

int main() {
    // Initialize host data
    for (int i = 0; i < SIZE; ++i) {
        host_data[i] = (float)i;
    }

    // Copy data to device
    float* device_ptr = acc_copyin(host_data, SIZE * sizeof(float));

    // Use OpenACC to process the data
    #pragma acc kernels present(device_ptr[0:SIZE])
    for (int i = 0; i < SIZE; ++i) {
        device_ptr[i] *= 2.0f;
    }

    // Copy data back to host
    acc_copyout(device_data, SIZE * sizeof(float));

    // Validate the results
    for (int i = 0; i < SIZE; ++i) {
        assert(device_data[i] == host_data[i] * 2.0f);
    }

    // Delete the data from the device
    acc_delete(device_ptr, SIZE * sizeof(float));

    // Try to copy data back again (should fail due to removed data)
    float backup_data[SIZE];
    acc_copyout(backup_data, SIZE * sizeof(float));
    for (int i = 0; i < SIZE; ++i) {
        assert(backup_data[i] != host_data[i] * 2.0f);
    }

    printf("Test passed\n");
    return 0;
}