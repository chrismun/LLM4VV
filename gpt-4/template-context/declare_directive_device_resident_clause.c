#include <stdio.h>
#include <openacc.h>

#define ARR_SIZE 100
#define NUM_TEST_CALLS 10

float a[ARR_SIZE];

// The "device_resident" clause specifies that the array 'a' will be available on the device for the duration of the program.
#pragma acc declare device_resident(a)

int test_func() {
    for(int i=0; i<ARR_SIZE; ++i) {
        // Initialize array on the host
        a[i] = (float) i;
    }

    // Compute on the device
    #pragma acc parallel loop
    for(int i=0; i<ARR_SIZE; ++i) {
        a[i] = a[i] * 2.0f;
    }

    // Check the result on the host
    for(int i=0; i<ARR_SIZE; ++i) {
        if(a[i] != i*2.0f) {
            return 1;  // error
        }
    }
    return 0;  // no error
}

int main() {
    int failcode = 0;
    int failed;

    for (int x=0; x<NUM_TEST_CALLS; ++x) {
        failed = test_func();
        if(failed != 0) {
            failcode = failcode + (1 << x);
        }
    }
    return failcode;
}