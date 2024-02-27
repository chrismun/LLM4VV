#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Define host variables
    int *a_host = (int*)malloc(10 * sizeof(int));
    int *a_device;
    
    bool is_present_before, is_present_after;

    // Initialize host memory
    for (int i = 0; i < 10; ++i){
        a_host[i] = rand() / (float)RAND_MAX * 100;
    }
    
    // Check if a_host is already present on the device
    is_present_before = acc_is_present(a_host, 10 * sizeof(int));
    
    // Allocate memory on the device and copy data from host to device
    #pragma acc enter data copyin(a_host[0:10])
    
    // Use no_create clause for a_host, expecting no new memory allocation or data movement
    #pragma acc parallel loop no_create present(a_host[0:10])
    for (int i = 0; i < 10; ++i){
        a_host[i] = a_host[i] * 2;
    }
    
    // Check if a_host is still present on the device after the no_create operation
    is_present_after = acc_is_present(a_host, 10 * sizeof(int));

    // Deallocate memory from the device without copying back to host
    #pragma acc exit data delete(a_host[0:10])
    
    // Check if the 'no_create' clause has correctly not allocated new memory
    // and if the data has been correctly manipulated on the device side.
    // Since we used 'no_create', we expect 'is_present_before' to be false 
    // and 'is_present_after' to be true when 'acc_is_present' is checked right after entering data.
    if (!is_present_before && !is_present_after) {
        err = 1;
        printf("Failure: Device variables were not correctly handled with no_create clause.\n");
    }
    
    free(a_host);

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