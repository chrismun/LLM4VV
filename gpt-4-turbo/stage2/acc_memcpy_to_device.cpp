#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:acc_memcpy_to_device, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    size_t num_elements = 1024;    // Number of elements to transfer
    size_t bytes = num_elements * sizeof(int); // Size in bytes

    // Allocate memory on the host
    int *data_host_src = (int *)malloc(bytes);
    if (data_host_src == NULL) {
        std::cerr << "Failed to allocate host memory" << std::endl;
        return 1;
    }

    // Initialize host memory
    for (size_t i = 0; i < num_elements; ++i) {
        data_host_src[i] = rand() % 100; // Random values
    }

    // Allocate memory on the device using OpenACC
    int *data_dev_dest = (int *)acc_malloc(bytes);
    if (data_dev_dest == NULL) {
        std::cerr << "Failed to allocate device memory" << std::endl;
        free(data_host_src);
        return 1;
    }

    // Use acc_memcpy_to_device to transfer data from host to device
    acc_memcpy_to_device(data_dev_dest, data_host_src, bytes);

    // Allocate memory on host for verification
    int *data_verify = (int *)malloc(bytes);
    if (data_verify == NULL) {
        std::cerr << "Failed to allocate verification memory" << std::endl;
        acc_free(data_dev_dest);
        free(data_host_src);
        return 1;
    }

    // Copy data back to host for verification
    acc_memcpy_from_device(data_verify, data_dev_dest, bytes);

    // Verify data
    for (size_t i = 0; i < num_elements; ++i) {
        if (data_host_src[i] != data_verify[i]) {
            err = 1; // Error if the data doesn't match
            break;
        }
    }

    // Cleanup
    free(data_host_src);
    free(data_verify);
    acc_free(data_dev_dest);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}