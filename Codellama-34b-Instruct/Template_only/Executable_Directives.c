#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 100
    int num = rand() % 100 + 1;

    // Create an array of integers with the same number of elements as the random number
    int arr[num];

    // Initialize the array with random values
    for (int i = 0; i < num; i++) {
        arr[i] = rand() % 100 + 1;
    }

    // Create a new array with the same number of elements as the original array
    int new_arr[num];

    // Copy the values from the original array to the new array
    for (int i = 0; i < num; i++) {
        new_arr[i] = arr[i];
    }

    // Check if the values in the new array are the same as the original array
    for (int i = 0; i < num; i++) {
        if (new_arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

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