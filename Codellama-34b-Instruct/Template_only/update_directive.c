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

    // Create a second array to store the updated values
    int *updated_arr = (int *)malloc(sizeof(int) * 10);

    // Update the values in the second array using the update directive
    #pragma acc update device(updated_arr[0:10])

    // Check that the updated values are correct
    for (int i = 0; i < 10; i++) {
        if (updated_arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the arrays
    free(arr);
    free(updated_arr);

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