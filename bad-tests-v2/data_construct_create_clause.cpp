#include "acc_testsuite.h"
#ifndef T1
//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array with the create clause
    int* arr = (int*)acc_create(sizeof(int) * 10, NULL);

    // Check that the array was created successfully
    if (arr == NULL) {
        err = 1;
    }

    // Zero the array
    for (int i = 0; i < 10; i++) {
        arr[i] = 0;
    }

    // Check that the array is zeroed
    for (int i = 0; i < 10; i++) {
        if (arr[i] != 0) {
            err = 1;
        }
    }

    // Detach the array
    acc_detach(arr);

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