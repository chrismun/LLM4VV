#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include <math.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef PRECISION
#define PRECISION 1e-5
#endif

// Assuming n is predefined.
#ifndef n
#define n 100
#endif

int test_detach_attach(){
    int err = 0;
    float *a = (float*)malloc(n*sizeof(float));
    float *b_device, *b_host;
    float *b = (float*)malloc(n*sizeof(float));

    // Initialize array a
    for (int i = 0; i < n; ++i){
        a[i] = rand() / (float)RAND_MAX;
    }

    // Allocate memory on the device and get a device pointer
    b_device = acc_malloc(n * sizeof(float));

    // Ensure b points to b_device for the duration of the data region
    b_host = b; // Save host pointer
    b = b_device; // Point b to device memory

    #pragma acc enter data copyin(a[0:n], b[0:n])

    // Perform computation on the device
    #pragma acc parallel loop present(a, b)
    for (int i = 0; i < n; ++i){
        b[i] = sqrt(a[i]);
    }

    // Detach b from pointing to device memory, restoring its original host pointer
    b = b_host;

    // Copy data back to the host
    #pragma acc exit data copyout(b[0:n])

    // Validate results
    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - sqrt(a[i])) > PRECISION){
            err++;
        }
    }

    // Free device memory
    acc_free(b_device);

    free(a);
    free(b);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = test_detach_attach();

    if (failed > 0){
        failcode = 1; // Mark test as failed
    }

    if(failcode == 0){
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }

    return failcode;
}