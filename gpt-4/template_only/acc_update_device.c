#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

//T1:acc update device,V:2.7-3.3
int test_acc_update_device(){
    int err = 0;
    int n = 1000000;
    int *array_host, *array_device;

    array_host = (int*) malloc(n*sizeof(int));
    array_device = (int*) acc_malloc(n*sizeof(int));

    // Initialize arrays on the host
    for (int i = 0; i < n; ++i){
        array_host[i] = i;
    }

    // Update device with host
    acc_memcpy_to_device(array_device, array_host, n*sizeof(int));

    // Update host with device
    acc_memcpy_from_device(array_host, array_device, n*sizeof(int));

    // Check for errors
    for (int i = 0; i < n; ++i){
        if (array_host[i] != i){
            err += 1;
        }
    }

    // Free resources
    free(array_host);
    acc_free(array_device);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;

    // Repeat test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_update_device();
    }
    
    if (failed != 0){
        failcode = failcode + (1 << 0);   // Shift bits to the left if there are failed tests
    }

    return failcode;
}