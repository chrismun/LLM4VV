#include "openacc.h"
#include <stdio.h>

int main() {
    int dataSize = 10;
    int failFlag = 0;
    
    // Initialize an array on the host
    int* hostArray = (int*)malloc(dataSize * sizeof(int));
    for (int i = 0; i < dataSize; ++i) {
        hostArray[i] = i;
    }

    // Copy the array to the device
    int* deviceArray;
    #pragma acc data create(deviceArray[0:dataSize])
    {
        #pragma acc host_data use_device(deviceArray)
        {
            memcpy(deviceArray, hostArray, dataSize * sizeof(int));
        }
    }

    // Use acc_hostptr() to get the host pointer
    int* hostPtrFromDevicePtr = (int *)acc_hostptr((void*)deviceArray);

    // Check if the returned host pointer is correct
    for (int i = 0; i < dataSize; ++i) {
        if (hostPtrFromDevicePtr[i] != hostArray[i]) {
            printf("Mismatch at position %d: hostArray[%d] = %d, hostPtrFromDevicePtr[%d] = %d \n",
                i, i, hostArray[i], i, hostPtrFromDevicePtr[i]);
            failFlag = 1;
        }
    }

    if (failFlag == 0){
        printf("Test Passed, acc_hostptr() function returned the correct host pointer.\n");
    }
    else{
        printf("Test Failed, acc_hostptr() function did not return the correct host pointer.\n");
    }

    return failFlag;
}