#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "acc_testsuite.h"

#define SIZE 100

int test1(){
    int err = 0;
    srand(SEED);

    int original[SIZE];
    int cached[SIZE];

    // Initialize the original array with random numbers
    for (int i = 0; i < SIZE; i++) {
        original[i] = rand() % 100;
    }

    // Copy the original array to the cached array
    for (int i = 0; i < SIZE; i++) {
        cached[i] = original[i];
    }

    // Use the cache directive to cache the original array
    #pragma acc cache(original)
    {
        // Check if the cached array is the same as the original array
        for (int i = 0; i < SIZE; i++) {
            if (original[i] != cached[i]) {
                err = 1;
                break;
            }
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}