#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test: Shutdown directive in OpenACC
// T1:shutdown directive,V:2.7-3.3
int test_shutdown_directive(){
    int err = 0;
    srand(SEED);

    int num_devices = acc_get_num_devices(acc_device_default);
    if (num_devices == 0) {
        printf("No devices available for testing\n");
        return 1; // Indicate error as no devices available to test with
    }

    // Assuming a simple vector addition to perform on the device
    size_t n = 1000;
    float *a, *b, *c;
    a = (float*)malloc(sizeof(float)*n);
    b = (float*)malloc(sizeof(float)*n);
    c = (float*)malloc(sizeof(float)*n);

    // Initialize vectors
    for (size_t i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }
    
    // Perform calculation on default device
    #pragma acc parallel loop copyin(a[0:n],b[0:n]) copyout(c[0:n])
    for (size_t i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    // Shutdown device
    #pragma acc shutdown

    // After shutdown all device memory and compute capabilities should be freed/disabled.

    // Test: Attempt to use device post shutdown. Should fail if shutdown was successful.
    err = 0;
    #pragma acc parallel loop copyin(a[0:n],b[0:n]) copyout(c[0:n]) if(0) // This should not execute
    for (size_t i = 0; i < n; i++) {
        // This code block is intended not to execute, demonstrating device shutdown
        err = 1; // Indicate error in shutdown if executed
    }

    free(a);
    free(b);
    free(c);

    return err; // 0 if shutdown was successful, 1 otherwise
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_shutdown_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("OpenACC shutdown directive test PASSED\n");
    } else {
        printf("OpenACC shutdown directive test FAILED\n");
    }
    
    return failcode;
}