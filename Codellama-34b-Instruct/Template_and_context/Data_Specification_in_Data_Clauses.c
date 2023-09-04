#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SEED 123456789
#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *arr = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100;
    }

    // Create a device pointer to the array
    int *dev_arr;
    acc_malloc((void **)&dev_arr, sizeof(int) * 100);
    acc_memcpy_to_device(dev_arr, arr, sizeof(int) * 100);

    // Create a host pointer to the array
    int *host_arr = (int *)malloc(sizeof(int) * 100);
    acc_memcpy_from_device(host_arr, dev_arr, sizeof(int) * 100);

    // Verify that the host and device pointers point to the same data
    for (int i = 0; i < 100; i++) {
        if (host_arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device and host pointers
    acc_free(dev_arr);
    free(host_arr);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}