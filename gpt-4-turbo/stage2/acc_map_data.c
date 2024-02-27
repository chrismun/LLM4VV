#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// A simple utility function to check for OpenACC errors
void check_acc_error(void) {
    acc_error_t error = acc_get_last_error();
    if (error != acc_no_error) {
        const char* err_str = acc_get_error_string(error);
        fprintf(stderr, "OpenACC Error: %s\n", err_str);
        exit(1);
    }
}

// Test for acc_map_data
int test_acc_map_data() {
    int err = 0;
    srand(SEED);

    const int array_size = 1024;
    float *host_array = (float *)malloc(array_size * sizeof(float));
    if (!host_array) {
        fprintf(stderr, "Failed to allocate host memory.\n");
        return 1; // Return nonzero indicating failure to allocate memory
    }

    // Initialize host array
    for (int i = 0; i < array_size; ++i) {
        host_array[i] = rand() / (float)RAND_MAX;
    }

    // Allocate device memory manually
    float *device_array = (float *)acc_malloc(array_size * sizeof(float));
    check_acc_error();
    if (!device_array) {
        fprintf(stderr, "Failed to allocate device memory.\n");
        free(host_array);
        return 1; // Return nonzero indicating failure to allocate device memory
    }

    // Map previously allocated device memory to the host array
    acc_map_data(host_array, device_array, array_size * sizeof(float));
    check_acc_error();

    // Perform a simple computation involving the mapped data to verify correctness
#pragma acc parallel loop present(host_array)
    for (int i = 0; i < array_size; ++i) {
        host_array[i] = host_array[i] * 2.0f;
    }
    check_acc_error();

    // Copy data back to host for verification
    acc_memcpy_from_device(host_array, device_array, array_size * sizeof(float));
    check_acc_error();

    // Verify computations
    for (int i = 0; i < array_size; ++i) {
        if (fabs(host_array[i] / 2.0f - (rand() / (float)RAND_MAX)) > 1e-5) {
            err = 1; // Error in computation, set err to nonzero
            break;
        }
    }

    // Cleanup
    acc_unmap_data(host_array);
    check_acc_error();
    acc_free(device_array);
    free(host_array);

    return err; // Return 0 if success, nonzero otherwise
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test_acc_map_data();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("All OpenACC acc_map_data tests passed.\n");
    } else {
        printf("Some OpenACC acc_map_data tests failed.\n");
    }

    return failcode;
}