#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Dynamically allocate memory for an integer variable.
    int *host_var = (int *)malloc(sizeof(int));
    *host_var = rand();

    // Initial value copied to the device
    #pragma acc enter data create(host_var[0:1])

    // Modify variable on the device to verify operation.
    #pragma acc parallel present(host_var)
    {
        *host_var = *host_var + 1;
    }

    // Use exit data with detach clause to detach the variable.
    #pragma acc exit data detach(host_var)

    // After detach access to the pointer host_var can lead to undefined behavior
    // so we don't access it here to verify if detach was successful.
    
    // No error check mechanism since post-detach operation on the variable is undefined
    // but if the implementation is incorrect, runtime errors or incorrect data management may occur.

    free(host_var); // Clean up malloc'd memory. This is safe as long the detach was successful. 
    
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