#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100;
    }

    // Map the array to the device
    acc_map_data(arr, 100, sizeof(int), acc_device_default);

    // Verify that the data has been mapped correctly
    for (int i = 0; i < 100; i++) {
        if (arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Unmap the array from the device
    acc_unmap_data(arr);

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