c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory for the data
    int *data = (int *)malloc(sizeof(int) * 10);
    int *data_copy = (int *)malloc(sizeof(int) * 10);

    // Initialize the data
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    // Copy the data to the device
    acc_copyin(data, sizeof(int) * 10);

    // Copy the data from the device to the host
    acc_copyout(data_copy, sizeof(int) * 10);

    // Check if the data has been successfully copied
    for (int i = 0; i < 10; i++) {
        if (data[i] != data_copy[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(data);
    free(data_copy);

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