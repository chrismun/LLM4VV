#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int *hostArray, *deviceArray;
    const int size = 1024;
    size_t bytes = size * sizeof(int);

    srand(SEED);

    // Allocate memory on the host
    hostArray = (int*)malloc(bytes);

    // Initialize host array
    for(int i = 0; i < size; ++i) {
        hostArray[i] = rand() % 100;
    }

    // Allocate memory on the device and copy data from the host
    #pragma acc enter data copyin(hostArray[0:size])

    // Use host_data construct with use_device clause to get device pointer
    #pragma acc host_data use_device(hostArray)
    {
        deviceArray = acc_deviceptr(hostArray);

        // Simulated "low-level API call" using the device pointer directly
        // For this demonstration, we invert the values (assuming operation by a hypothetical API)
        #pragma acc parallel loop present(hostArray)
        for(int i = 0; i < size; ++i) {
            hostArray[i] = 100 - hostArray[i];
        }
    }

    // Copy data back to host
    #pragma acc exit data copyout(hostArray[0:size])

    // Verification
    for(int i = 0; i < size; ++i) {
        if (hostArray[i] != (100 - (rand() % 100))) {
            err++;
            break;
        }
    }

    free(hostArray);
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
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}