#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
// Assuming acc_testsuite.h defines SEED and NUM_TEST_CALLS appropriately
#include "acc_testsuite.h"

#ifndef T1
// T1:acc_hostptr, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test starts here
    int host_data = 42; // A simple int to test
    int *host_ptr = &host_data; // Pointer to host_data

    // Copy data to the device, it should return a device pointer
    int *device_ptr = acc_copyin(&host_data, sizeof(int));

    // Retrieve host pointer from the device pointer
    int *retrieved_host_ptr = (int *)acc_hostptr(device_ptr);

    // Check if the retrieved host pointer matches the original host pointer
    if (retrieved_host_ptr != host_ptr) {
        printf("Error: Retrieved host pointer does not match the original host pointer.\n");
        err++;
    }

    // Clean up: Since we used acc_copyin, data is automatically managed by OpenACC

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}