#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Ensure to include OpenACC header
#include <math.h>

#define SEED 12345
#define n 1000
#define PRECISION 0.001

int main() {
    int err = 0;
    srand(SEED);
    float *host_array = (float *)malloc(n * sizeof(float)); // Allocate host memory
    for (int i = 0; i < n; ++i) {
        host_array[i] = rand() / (float)(RAND_MAX / 10); // Initialize host array
    }

    // Allocate device memory using acc_malloc
    float *device_array = (float *)acc_malloc(n * sizeof(float));
    if (device_array == NULL) {
        printf("Device memory allocation failed\n");
        return -1;
    }

    // Map host array to device array using acc_map_data
    acc_map_data(host_array, device_array, n * sizeof(float));

    // Perform operations on device memory
    #pragma acc parallel loop present(device_array)
    for (int i = 0; i < n; ++i) {
        device_array[i] = host_array[i] + 1;  // Modify data in device memory
    }

    // Host array should reflect changes made to device_array without explicit copyout
    for (int i = 0; i < n; ++i) {
        if (fabs(host_array[i] - (rand() / (float)(RAND_MAX / 10) + 1)) > PRECISION) {
            err++;
        }
    }

    // Unmap the data - ensuring it's a clean state
    acc_unmap_data(host_array);

    // Cleanup and Exit
    acc_free(device_array);
    free(host_array);

    if (err == 0) {
        printf("Test Passed: host_array reflects changes made to device_array.\n");
    } else {
        printf("Test Failed: %d elements did not reflect expected changes.\n", err);
    }

    return err;
}