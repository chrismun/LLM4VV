#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *arr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Create a copy of the array on the device
    int *dev_arr = (int *)acc_copyin(arr, sizeof(int) * 10);

    // Modify the array on the device
    for (int i = 0; i < 10; i++) {
        dev_arr[i] = dev_arr[i] + 1;
    }

    // Copy the modified array back to the host
    acc_copyout(dev_arr, arr, sizeof(int) * 10);

    // Check that the array on the host has been modified
    for (int i = 0; i < 10; i++) {
        if (arr[i] != dev_arr[i]) {
            err = 1;
            break;
        }
    }

    // Delete the device array
    acc_delete(dev_arr);

    // Check that the device array has been deleted
    if (acc_is_present(dev_arr)) {
        err = 1;
    }

    // Free the host array
    free(arr);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}