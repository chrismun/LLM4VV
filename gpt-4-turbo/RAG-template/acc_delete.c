#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));

    // Initialize the array
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
    }

    // Ensure data is present on the device
    #pragma acc enter data copyin(a[0:size])

    // Perform some operations on the device
    #pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i){
        a[i] += 1;
    }
    
    // Use the runtime API to delete the data from the device memory
    acc_delete((void*)a, size * sizeof(int));

    // Trying to access data on the device should now result in an acc_error_not_present error
    int error_caught = 0;
    #pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i){
        a[i] += 1;  // This line should not be executed
    }
    if(!error_caught){
        printf("Expected acc_error_not_present error was not caught.\n");
        err += 1;
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