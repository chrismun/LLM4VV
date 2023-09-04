#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *arr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a device array to store the data
    int *dev_arr = (int *)malloc(sizeof(int) * 10);

    // Enter the data into the device array
    #pragma acc enter data copyin(arr[0:10])

    // Verify that the data was entered correctly
    for (int i = 0; i < 10; i++) {
        if (arr[i] != dev_arr[i]) {
            err = 1;
            break;
        }
    }

    // Exit the data from the device array
    #pragma acc exit data delete(arr[0:10])

    // Verify that the data was exited correctly
    for (int i = 0; i < 10; i++) {
        if (arr[i] != dev_arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    free(dev_arr);

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