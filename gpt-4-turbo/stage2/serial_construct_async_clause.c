#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        a[i] = 0; // Initialize array with 0
    }

    // Using serial construct with async clause
    #pragma acc serial async(1)
    for (int i = 0; i < size; ++i){
        a[i] = 1; // Modify array asynchronously
    }

    // Wait for the asynchronous operation to complete
    #pragma acc wait(1)

    // Verify if the operations completed as expected
    for (int i = 0; i < size; ++i){
        if (a[i] != 1){
            err++;
        }
    }

    free(a);
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