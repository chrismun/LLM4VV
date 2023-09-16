#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 100

int main()
{
    // Initialize an array on the host
    int *hostArray = (int*)malloc(ARRAY_SIZE*sizeof(int));
    for(int i=0; i<ARRAY_SIZE; i++){
        hostArray[i] = i;
    }

    // Create a data region and map the array to the device
    #pragma acc data create(hostArray[0:ARRAY_SIZE])
    {
        // Nothing here for now.
    }

    // Test use_device clause
    int error_count = 0;
    #pragma acc data present(hostArray[0:ARRAY_SIZE])
    {
        int* devicePtr = acc_deviceptr(hostArray);
        #pragma acc host_data use_device(devicePtr)
        {
            int* sameDevicePtr = acc_deviceptr(hostArray);
            if(devicePtr != sameDevicePtr) {
                printf("Error: Different device pointers returned.\n");
                error_count++;
            }
        }
    }
    
    // Check error count
    if(error_count == 0) {
        printf("Success: OpenACC host_data use_device() clause was implemented correctly.\n");
    } else {
        printf("Test failed.\n");
    }

    // Free allocated memory
    free(hostArray);
    
    return 0;
}