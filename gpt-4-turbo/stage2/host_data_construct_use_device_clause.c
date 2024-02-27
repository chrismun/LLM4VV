#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1;
    int *hostData = (int*)malloc(size * sizeof(int));
    int *deviceData;

    // Allocate memory on the device
    deviceData = (int*)acc_malloc(size * sizeof(int));

    // Initialize device memory to verify the use_device clause works
    #pragma acc parallel loop copyout(deviceData[0:size])
    for(int i = 0; i < size; i++){
        deviceData[i] = i;
    }

    // Use the host_data construct with the use_device clause
    #pragma acc host_data use_device(deviceData)
    {
        // Supposed to access the deviceData directly
        // For demonstration, simply assign the value back to hostData for verification
        *hostData = *deviceData; 
    }

    // Verify the operation - in a real test, additional verification may be necessary
    if(*hostData != 0){
        err++;
    }

    // Cleanup
    free(hostData);
    acc_free(deviceData);

    return err;
}
#endif

int main(){
    const int NUM_TEST_CALLS = 10;
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}