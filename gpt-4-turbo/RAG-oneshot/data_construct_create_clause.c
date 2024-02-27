// Include OpenACC support
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 1e-5

// Test function for the create clause
int test_create_clause() {
    int err = 0;
    float *hostArray = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float *deviceArray; // Pointer for device array, will use create clause to allocate

    // Initialize host array with some values
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        hostArray[i] = i * 1.0f;
    }

    // Allocate memory on the device but do not initialize it (create)
    #pragma acc data create(deviceArray[0:NUM_ELEMENTS])
    {
        // Inside this region, deviceArray is expected to be allocated on the device
    }

    // Copy data from host to device manually
    #pragma acc update device(deviceArray[0:NUM_ELEMENTS])
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        deviceArray[i] = hostArray[i];
    }

    // Copy back the data to the host to verify content
    float *verifyArray = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    #pragma acc update host(verifyArray[0:NUM_ELEMENTS]) 

    // Perform verification
    for(int i = 0; i < NUM_ELEMENTS; ++i) {
        if(fabs(verifyArray[i] - hostArray[i]) > PRECISION) {
            err++;
        }
    }

    free(hostArray);
    free(verifyArray);
    
    return err;
}

int main() {
    int failCount = test_create_clause();

    if(failCount == 0) {
        printf("Test Passed, create clause works as expected.\n");
    } else {
        printf("Test Failed, %d mismatches found.\n", failCount);
    }

    return failCount;
}