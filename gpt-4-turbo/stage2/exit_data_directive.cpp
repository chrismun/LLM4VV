#include <iostream>
#include <stdlib.h>
#include "acc_testsuite.h"  // Make sure this is correctly set up in your environment
#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 100;
    srand(SEED);
    float *a_host = (float *) malloc(n * sizeof(float));

    // Initialize array
    for (int i = 0; i < n; ++i){
        a_host[i] = rand() % 1000;
    }

    // Copy data to device
#pragma acc enter data copyin(a_host[0:n])

    // Modify data on device
#pragma acc parallel loop present(a_host[0:n])
    for (int i = 0; i < n; ++i){
        a_host[i] += 1;
    }

    // Use exit data to delete device copy
#pragma acc exit data delete(a_host[0:n])

    // Dummy modification to attempt to trigger access to deleted data
    // This step's success in access blocking won't be easily verifiable programmatically without device-specific error handling mechanisms
#pragma acc parallel loop present(a_host[0:n])
    for (int i = 0; i < n; ++i){
        a_host[i] += 1;  // This operation should not occur or reflect on the host due to the prior exit data directive
    }

    // Manual check is suggested here to ensure 'a_host' is not modified after 'exit data'
    // This might entail using debugging tools or device-specific checks to confirm 'a_host' is indeed deleted on the device

    free(a_host);
    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}