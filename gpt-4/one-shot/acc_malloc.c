#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000

int main(void) {
    float* devicePtr;
    float* hostPtr = (float *) malloc(SIZE * sizeof(float));

    //Fill with some initial values
    for (int i = 0; i < SIZE; i++) {
        hostPtr[i] = (float)rand()/(float)(RAND_MAX);
    }

    // Allocate on the device
    devicePtr = (float *) acc_malloc(SIZE * sizeof(float));
    if(devicePtr == NULL){
        printf("Device memory allocation failed\n");
        return -1;
    }
    // Copy data to device
    acc_memcpy_to_device(devicePtr, hostPtr, SIZE * sizeof(float));

    // Copy data back to host
    acc_memcpy_from_device(hostPtr, devicePtr, SIZE * sizeof(float));

    //Free device memory
    acc_free(devicePtr);

    // Checking final values
    for (int i = 0; i < SIZE; i++) {
        if (abs(hostPtr[i] - ((float)rand()/(float)(RAND_MAX))) > 1e-5) {
            printf("Error at position %d. Expected %f. Got %f\n", i, hostPtr[i], ((float)rand()/(float)(RAND_MAX)));
            return -1;
        }
    }

    printf("Test passed\n");
    return 0;
}