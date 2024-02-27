#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Mock test suite utility functions and macros, to replace with actual ones in a full testsuite environment
#define acc_testsuite.h

int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory for testing
    int *host_ptr = (int*) malloc(sizeof(int));
    *host_ptr = rand(); // Assign a random value

    // Explicitly allocate device memory and attach the host pointer to this device pointer
    int *device_ptr = (int *) acc_malloc(sizeof(int));
    acc_attach((void **)&host_ptr);

    // Modify the device data to simulate a computation or modification that happens on the device
    #pragma acc parallel present(host_ptr)
    {
        *host_ptr += 5; // Sample operation
    }

    // Before detaching, copy back the modified data to verify
    acc_memcpy_from_device(host_ptr, device_ptr, sizeof(int));

    // Detach the pointer, which after this, host_ptr should refer back to the host memory
    acc_detach((void **)&host_ptr);

    // After detaching, perform an operation on host_ptr to verify it points to the original host memory
    *host_ptr -= 5;

    // Validate if the operation after detaching affected the original host memory, indicating detaching worked
    if(*host_ptr != rand()){
        printf("Detach failed: host_ptr does not point to the original host memory after detaching.");
        err = 1;
    }

    // Clean up
    free(host_ptr);
    acc_free(device_ptr);

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