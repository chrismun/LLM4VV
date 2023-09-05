#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

void initializeArray(float *arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
}

int main() {
    float *hostArray = (float *) malloc(N * sizeof(float));
    float *deviceArray = (float *) malloc(N * sizeof(float));

    // Initialize hostArray
    initializeArray(hostArray, N);

    // Copy hostArray to deviceArray
    #pragma acc data copyin(hostArray[0:N]) copyout(deviceArray[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            deviceArray[i] = hostArray[i] + 1;
        }
    }

    // Print deviceArray
    printf("Device array:\n");
    for (int i = 0; i < N; ++i) {
        printf("%.1f ", deviceArray[i]);
    }
    printf("\n");

    // Free memory
    free(hostArray);
    free(deviceArray);

    return 0;
}