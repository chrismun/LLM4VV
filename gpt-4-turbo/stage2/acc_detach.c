#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test for acc_detach
// T1:acc_detach, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Allocate host memory and initialize it
    float *host_ptr = (float *)malloc(sizeof(float));
    *host_ptr = 42.0f; // Arbitrary value for testing
    
    // Use acc_attach to make the host_ptr available on the device
    acc_attach((void **)&host_ptr);
    
    // Modify host_ptr value on the device
    #pragma acc parallel copy(host_ptr[0:1])
    {
        host_ptr[0] = 84.0f; // Change the value
    }
    
    // Detach the pointer from device memory, reverting it back to host
    acc_detach((void **)&host_ptr);
    
    // Attempt to modify the pointer value on the device after detachment -- should fail if detached correctly
    int capture_err = 0;
    #pragma acc parallel copy(capture_err)
    {
        if (acc_is_present(host_ptr, sizeof(float))) {
            capture_err = 1; // Error if still present on the device
        }
    }
    
    if (capture_err != 0) {
        printf("Error: host_ptr is still present on the device after acc_detach.\n");
        err = 1;
    }
    
    // Device memory should not be accessible, hence original value should remain unchanged
    if (*host_ptr != 42.0f) {
        printf("Error: The value of host_ptr was altered to %f, expected 42.0f.\n", *host_ptr);
        err = 1;
    }
    
    free(host_ptr);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        if(test1() != 0) {
            failed++;
        }
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    if (failcode == 0) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }
    
    return failcode;
}