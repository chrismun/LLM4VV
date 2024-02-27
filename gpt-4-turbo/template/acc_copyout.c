#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:{feature}, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int arraySize = 1024;
    int *a = (int *)malloc(sizeof(int) * arraySize);
    // Initialize array with test values
    for (int i = 0; i < arraySize; ++i) {
        a[i] = -1; // Initialized to a default value
    }

    // Perform the parallel operation and copy result back to a
#pragma acc parallel copyout(a[0:arraySize])
    {
        for (int i = 0; i < arraySize; ++i) {
            a[i] = i; // Simulate some computation
        }
    }

    // Verify that the data has been updated correctly
    for (int i = 0; i < arraySize; ++i) {
        if (a[i] != i) {
            err++;
            break;
        }
    }

    free(a); // Clean up allocated memory

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
        // Encoding the specific test that failed into the failcode
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}