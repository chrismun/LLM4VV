#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Copy the array to the device
    #pragma acc enter data copyin(arr[:10])

    // Modify the array on the device
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        arr[i] += 1;
    }

    // Copy the modified array back to the host
    #pragma acc exit data copyout(arr[:10])

    // Check that the array has been modified correctly
    for (int i = 0; i < 10; i++) {
        if (arr[i] != (rand() + 1)) {
            err = 1;
            break;
        }
    }

    // Free the memory
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