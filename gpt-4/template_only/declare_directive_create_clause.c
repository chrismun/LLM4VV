#include <stdlib.h>
#include <openacc.h>

// This length can be modified as per your requirement
#define ARRAY_LENGTH 1024

// Array which will be used in the test must be declared globally
float array[ARRAY_LENGTH];

#pragma acc declare create(array)

int test_array_content() {
    int i, isError = 0;
    
    // Initialize array on host
    for (i = 0; i < ARRAY_LENGTH; i++) array[i] = i;

    // Performs operations on device using OpenACC kernels
    #pragma acc kernels
    {
        for (i = 0; i < ARRAY_LENGTH; i++) {
            array[i] = array[i] * 2.0;
        }
    }

    // Verify array content after operations on device
    for (i = 0; i < ARRAY_LENGTH; i++) {
        if (array[i] != i * 2.0) {
            isError = 1;
            break;
        }
    }

    return isError;
}

int main() {
    int testError;

    testError = test_array_content();

    if(testError) {
        printf("Test failed\n");
        return 1;
    } else {
        printf("Test Passed\n");
        return 0;
    }
}