#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 1000
#define PRECISION 0.0001

typedef float real_t; // Define real_t as per your requirements, float or double for instance.

int test_copyout(){
    int err = 0;
    srand(42); // Use a fixed seed for reproducibility.
    real_t *host_array = (real_t *)malloc(n * sizeof(real_t));
    real_t *device_mirror = (real_t *)malloc(n * sizeof(real_t));

    // Initialize host_array with random values and device_mirror with zeros.
    for (int i = 0; i < n; ++i){
        host_array[i] = rand() / (real_t)(RAND_MAX / 10);
        device_mirror[i] = 0;
    }

    // Copy the data to the device and perform computation.
    #pragma acc parallel copyin(host_array[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            // Simulate some operations that change the value in host_array.
            host_array[i] *= 2.0;
        }
    }

    // Copy out the modified data from device to device_mirror.
    #pragma acc parallel copyout(device_mirror[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            device_mirror[i] = host_array[i]; // host_array modified values are transferred to device_mirror.
        }
    }

    // Verification: Check if the host_array data modifications are reflected in device_mirror after copyout.
    for (int i = 0; i < n; ++i){
        if (fabs(device_mirror[i] - (2.0 * host_array[i])) > PRECISION){
            printf("Mismatch at element %d: host_array=%.6f, device_mirror=%.6f\n", i, host_array[i], device_mirror[i]);
            err += 1;
        }
    }

    free(host_array);
    free(device_mirror);

    return err;
}

int main(){
    int failcode = 0;

    int errors = test_copyout();
    if (errors > 0){
        printf("Test FAILED with %d errors.\n", errors);
        failcode = 1;
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}