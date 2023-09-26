#include <stdio.h>
#include <openacc.h>

#define ARRAY_SIZE 100

int main() {
    double a[ARRAY_SIZE];
    double b[ARRAY_SIZE];
    int err = 0;

    // Initialize arrays
    for(int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = (double)i;
        b[i] = 0.0;
    }

    // Use device_type clause to run loop on specific device
    #pragma acc parallel loop device_type(multicore) copyout(b[0:ARRAY_SIZE])
    for(int i = 0; i < ARRAY_SIZE; i++) {
        b[i] = a[i];
    }

    // Verification
    for(int i = 0; i < ARRAY_SIZE; i++) {
        if(b[i] != a[i]) {
            printf("Error at index %d: expected %g, got %g\n", i, a[i], b[i]);
            err++;
        }
    }

    if(err == 0) {
        printf("Test PASSED\n");
    }
    else {
        printf("Test FAILED\n");
    }

    return 0;
}