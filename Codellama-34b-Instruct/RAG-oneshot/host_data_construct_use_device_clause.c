#include <openacc.h>

int main() {
    int failcode = 0;
    int failed;

    // Create a device pointer
    int *dev_ptr = (int *)acc_malloc(sizeof(int));

    // Initialize the device pointer with a value
    *dev_ptr = 10;

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));

    // Initialize the host pointer with a value
    *host_ptr = 20;

    // Use the host_data construct with the use_device clause to
    // copy the device pointer to the host pointer
    #pragma acc host_data use_device(dev_ptr)
    {
        // Copy the device pointer to the host pointer
        *host_ptr = *dev_ptr;
    }

    // Check that the host pointer has the same value as the device pointer
    if (*host_ptr != *dev_ptr) {
        failcode = 1;
    }

    // Free the device and host pointers
    acc_free(dev_ptr);
    free(host_ptr);

    return failcode;
}