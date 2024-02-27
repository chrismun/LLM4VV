#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1024
#define PRECISION 1e-5

int test_acc_deviceptr(){
    int err = 0;
    float *hostArray = (float *)malloc(N * sizeof(float)); // Allocate memory on host
    float *devicePtr, *dummyPtr;
    
    // Initialize host array with some values
    for(int i = 0; i < N; i++){
        hostArray[i] = i * 1.0f;
    }

    // Make sure the data is present on the device
    #pragma acc enter data copyin(hostArray[0:N])

    // Use acc_deviceptr to get the device pointer
    devicePtr = (float *)acc_deviceptr(hostArray);
    
    if (devicePtr == NULL){
        printf("Device pointer should not be NULL. Test failed.\n");
        err++;
    } else {
        printf("Device pointer obtained.\n");
    }

    // Try to get device pointer for memory not present on device
    float notOnDevice;
    dummyPtr = (float *)acc_deviceptr(&notOnDevice);
    if (dummyPtr != NULL){
        printf("Expected NULL for memory not present on the device. Test failed.\n");
        err++;
    }
    
    // Cleanup
    #pragma acc exit data delete(hostArray[0:N])

    free(hostArray);
    return err;
}

int main() {
    int fail = test_acc_deviceptr();
    if (fail) {
        printf("Test FAILED with %d errors.\n", fail);
    } else {
        printf("Test PASSED.\n");
    }

    return fail;
}