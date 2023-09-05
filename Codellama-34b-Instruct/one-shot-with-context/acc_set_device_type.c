#include <openacc.h>

int main() {
    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_GPU);

    // Create a compute region
    #pragma acc parallel
    {
        // Do some work on the GPU
    }

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_CPU);

    // Create a compute region
    #pragma acc parallel
    {
        // Do some work on the CPU
    }

    return 0;
}