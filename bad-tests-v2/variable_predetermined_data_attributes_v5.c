#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a device array and copy the host array to it
    int* dev_arr = (int*)acc_malloc(sizeof(int) * 10);
    acc_memcpy_to_device(dev_arr, arr, sizeof(int) * 10);

    // Create a predicate variable and set it to true
    int predicate = 1;

    // Use the predicate variable to determine which elements to copy to the device
    acc_copy_to_device(dev_arr, arr, sizeof(int) * 10, predicate);

    // Check that the elements that were not copied to the device are still on the host
    for (int i = 0; i < 10; i++) {
        if (arr[i] != dev_arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array and host array
    acc_free(dev_arr);
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