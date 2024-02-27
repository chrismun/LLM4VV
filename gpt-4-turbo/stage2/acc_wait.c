#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 42
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 100

// Simple function to initialize an array with random numbers.
void init_array(int* arr, int size) {
    for(int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;  // Random number between 0 and 99
    }
}

// Test function to evaluate the implementation of acc_wait
int test_acc_wait() {
    int errors = 0;
    int *host_array, *device_array;

    host_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    device_array = (int*)malloc(ARRAY_SIZE * sizeof(int));

    srand(SEED);
    init_array(host_array, ARRAY_SIZE);

    // Copy data to device and perform asynchronous operation
    #pragma acc data copyin(host_array[0:ARRAY_SIZE]) copyout(device_array[0:ARRAY_SIZE]) async(1)
    {
        #pragma acc parallel loop async(1)
        for (int i = 0; i < ARRAY_SIZE; i++) {
            device_array[i] = host_array[i] + 1;  // Simple computation to validate
        }
    }

    // Here we wait for the completion of all asynchronous operations on queue 1
    acc_wait(1);

    // Verification
    for(int i = 0; i < ARRAY_SIZE; ++i) {
        if(device_array[i] != host_array[i] + 1) {
            errors++;
        }
    }

    free(host_array);
    free(device_array);

    return errors;
}

int main() {
    int failcode = 0;

    for(int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test_acc_wait() != 0) {
            failcode = 1;  // Mark fail if any of the calls to test_acc_wait returns non-zero
            break;
        }
    }

    if(failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    
    return failcode;
}