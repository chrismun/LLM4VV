#include "acc_testsuite.h"

#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a device array to store the data
    int* dev_arr = (int*)acc_malloc(sizeof(int) * 10);

    // Copy the data to the device array
    acc_memcpy(dev_arr, arr, sizeof(int) * 10);

    // Create a variable to store the result of the reduction
    int result = 0;

    // Create a compute construct to perform the reduction
    #pragma acc parallel loop reduction(+:result)
    for (int i = 0; i < 10; i++) {
        result += dev_arr[i];
    }

    // Check the result of the reduction
    if (result != 45) {
        err = 1;
    }

    // Free the device array
    acc_free(dev_arr);

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