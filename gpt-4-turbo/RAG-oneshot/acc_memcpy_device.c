#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#define DATA_SIZE (1024)
#define PRECISION (1e-6)

int main() {
    float *host_src, *host_dest;
    float *device_src, *device_dest;
    int errors = 0;

    // Allocate memory on the host
    host_src = (float *)malloc(DATA_SIZE * sizeof(float));
    host_dest = (float *)malloc(DATA_SIZE * sizeof(float));

    // Initialize source data
    for (int i = 0; i < DATA_SIZE; i++) {
        host_src[i] = i;
    }

    // Allocate memory on the device for source and destination
    device_src = (float *)acc_malloc(DATA_SIZE * sizeof(float));
    device_dest = (float *)acc_malloc(DATA_SIZE * sizeof(float));

    // Ensure allocations were successful
    if (device_src == NULL || device_dest == NULL) {
        fprintf(stderr, "Device memory allocation failed\n");
        return 1; // Return with error
    }

    // Copy initial data to device source
    acc_memcpy_to_device(device_src, host_src, DATA_SIZE * sizeof(float));

    // Use acc_memcpy_device to copy from device_src to device_dest
    acc_memcpy_device(device_dest, device_src, DATA_SIZE * sizeof(float));

    // Copy back the result to host memory for verification
    acc_memcpy_from_device(host_dest, device_dest, DATA_SIZE * sizeof(float));

    // Verify the copied data
    for (int i = 0; i < DATA_SIZE; i++) {
        if (fabs(host_dest[i] - host_src[i]) > PRECISION) {
            errors++;
        }
    }

    // Clean up
    acc_free(device_src);
    acc_free(device_dest);
    free(host_src);
    free(host_dest);

    if (errors == 0) {
        printf("Test passed. Data was successfully copied on the device.\n");
        return 0; // Return with success
    } else {
        printf("Test failed. %d errors found.\n", errors);
        return 1; // Return with error
    }
}