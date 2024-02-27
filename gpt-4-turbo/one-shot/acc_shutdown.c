#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define n 1000
#define PRECISION 0.00001

// Utility function to check computation validity
int validate(float* a, float* b) {
    for (int i = 0; i < n; ++i) {
        if (fabs(b[i] - (a[i] * a[i])) > PRECISION) {
            return 1; // Error found
        }
    }
    return 0; // No errors
}

int test_shutdown_behavior() {
    int err = 0;
    
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = 0;
    }

    // First offload: should work as expected
    #pragma acc parallel loop copyin(a[0:n]) copyout(b[0:n])
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] * a[i];
    }
    err += validate(a, b);

    acc_shutdown(acc_device_default); // Shutdown the accelerator

    // Second offload attempt post shutdown
    // Depending on implementation specifics, this might not execute on the accelerator.
    // The test here is basic, as behavior can be implementation-defined.
    #pragma acc parallel loop copyin(a[0:n]) copyout(b[0:n])
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] + a[i];
    }
    // Optionally, verify the above didn't actually execute as intended on an accelerator

    free(a);
    free(b);

    return err; // 0 indicates success, >0 indicates a problem in the first computation segment
}

int main() {
    int failcode = test_shutdown_behavior();
    if (failcode) {
        printf("Test failed\n");
    } else {
        printf("Test passed\n");
    }

    return failcode;
}