#include <stdio.h>
#include <openacc.h>

int main() {
    int hostArray[100], deviceArray[100];

    // Initialize host array
    for(int i=0; i<100; i++) {
        hostArray[i] = i;
    }

    // Copy data to the device
    #pragma acc data copyin(hostArray) copy(deviceArray)
    {
        // Copy the hostarray to deviceArray on the device
        #pragma acc parallel loop
        for(int i=0; i<100; i++) {
            deviceArray[i] = hostArray[i];
        }

        // Ensure that deviceArray remains consistent in a nested data region
        #pragma acc data copy(deviceArray)
        {
            #pragma acc parallel loop
            for(int i=0; i<100; i++) {
                if(deviceArray[i] != hostArray[i]) {
                    printf("Data inconsistency detected");
                    return -1;
                }
            }
        }
    }

    return 0;