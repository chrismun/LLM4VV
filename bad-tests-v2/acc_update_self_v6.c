#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 10000
#define UPDATE_VAL 5

int main(){
    int fail = 0;
    int *host_array, *device_array;

    // Allocate memory for host and device arrays 
    host_array = (int*)malloc(sizeof(int)*ARRAY_SIZE);
    device_array = (int*)malloc(sizeof(int)*ARRAY_SIZE);

    // Initialize host array with initial values
    for(int i=0; i<ARRAY_SIZE; i++){
        host_array[i] = i;
    }

    #pragma acc data create(device_array[0:ARRAY_SIZE]) copyin(host_array[0:ARRAY_SIZE])
    {
        #pragma acc parallel loop
        for(int i=0; i<ARRAY_SIZE; i++){
            device_array[i] = host_array[i];
        }

        // Simulating some operations that modifies the device array
        #pragma acc parallel loop
        for(int i=0; i<ARRAY_SIZE; i++){
            device_array[i] += UPDATE_VAL;
        }

        // Perform acc_update_self to sync the device array back to the host array
        acc_update_self(device_array, sizeof(int)*ARRAY_SIZE);
    }

    // Verify that device array was correctly updated back to the host array
    for(int i=0; i<ARRAY_SIZE; i++){
        if(host_array[i] != (i + UPDATE_VAL)){
            printf("Error: host_array[%d] = %d, expected %d\n", i, host_array[i], i+UPDATE_VAL);
            fail = 1;
            break;
        }
    }

    printf((fail == 1) ? "Test Failed\n" : "Test Passed\n");

    // Clean up
    free(host_array);
    free(device_array);

    return fail; 
}