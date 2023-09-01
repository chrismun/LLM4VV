#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of size 100
    int arr[100];

    // Initialize the array with random values
    for (int i = 0; i < 100; i++) {
        arr[i] = rand();
    }

    // Create a copy of the array
    int copy[100];
    memcpy(copy, arr, sizeof(arr));

    // Copy the array to the device
    #pragma acc enter data copyin(arr)

    // Create a new array on the device
    int *dev_arr;
    #pragma acc enter data create(dev_arr)

    // Copy the array from the device to the host
    #pragma acc exit data copyout(dev_arr)

    // Check if the array on the device is equal to the copy on the host
    if (memcmp(dev_arr, copy, sizeof(arr)) != 0) {
        err = 1;
    }

    // Clean up the device memory
    #pragma acc exit data delete(dev_arr)

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}