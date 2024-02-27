#include <stdio.h>
#include <openacc.h>
#include <math.h>

// Function to test if setting the device type works as expected
int test_set_device_type(acc_device_t device_type) {
    int err = 0;
    int vector_size = 1024;
    float *a = (float *)malloc(vector_size * sizeof(float));
    float *b = (float *)malloc(vector_size * sizeof(float));
    
    // Initialize vectors
    for (int i = 0; i < vector_size; i++) {
        a[i] = sinf(i) * sinf(i);
        b[i] = 0;
    }
    
    // Set the device type
    acc_set_device_type(device_type);
    acc_device_t current_device_type = acc_get_device_type();

    // Verify the device type has been set correctly
    if (current_device_type != device_type) {
        printf("Expected device type %d, but got %d\n", device_type, current_device_type);
        free(a);
        free(b);
        return 1;
    }
    
    // Using OpenACC parallel directive to perform operation
    #pragma acc data copyin(a[0:vector_size]) copyout(b[0:vector_size])
    {
        #pragma acc parallel loop
        for (int i = 0; i < vector_size; i++) {
            b[i] = sqrtf(a[i]);
        }
    }
    
    // Verify the operation was successful
    for (int i = 0; i < vector_size; i++) {
        if (fabs(sqrtf(a[i]) - b[i]) > 1e-6) {
            err++;
        }
    }
    
    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    
    // Test for NVIDIA GPU device if available
    if (acc_device_nvidia != -1 && !test_set_device_type(acc_device_nvidia)) {
        printf("Successfully set and tested device type to NVIDIA GPU.\n");
    } else {
        printf("Failed to set device type to NVIDIA GPU or to verify its operations.\n");
        failcode |= 1;
    }
    
    // Test for HOST device
    if (!test_set_device_type(acc_device_host)) {
        printf("Successfully set and tested device type to HOST.\n");
    } else {
        printf("Failed to set device type to HOST or to verify its operations.\n");
        failcode |= 2;
    }

    return failcode;
}