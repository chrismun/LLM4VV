#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int test1(){
    int err = 0;
    srand(SEED);
    int a[100];
    int initialValue = 5;

    // Initialize the array to check later if modifications have been isolated by private tmp
    for (int i = 0; i < 100; ++i) {
        a[i] = 0;
    }

    // Test starts
    #pragma acc data copy(a)
    {
        #pragma acc parallel loop private(initialValue)
        for (int i = 0; i < 100; ++i) {
            int tmp = initialValue; // tmp is private to each iteration
            tmp += i; // Modify tmp in a way that depends on the loop variable
            if (tmp != initialValue + i){
                err++; // This should never happen if tmp is truly private
            }
            a[i] = tmp; // Write the result back to check after
        }
    }

    // Verify that changes to tmp in the loop were isolated between iterations
    for (int i = 0; i < 100; ++i) {
        if (a[i] != initialValue + i) {
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}