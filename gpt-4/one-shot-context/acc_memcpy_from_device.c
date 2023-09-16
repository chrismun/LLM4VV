#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const int N = 100;
    int *device_array, *host_array;

    // Allocate host memory
    host_array = (int*) malloc(N*sizeof(int));

    // Allocate device memory
    device_array = (int*) acc_malloc(N*sizeof(int));

    // Initialize device memory using a OpenACC parallel loop
    #pragma acc parallel loop present_or_copyout(device_array[0:N])
    for(int i = 0; i < N; i++) {
        device_array[i] = i;
    }

    // Copy data from device memory to host memory
    acc_memcpy_from_device(host_array, device_array, N*sizeof(int));

    // Validate the data
    int error = 0;
    for(int i = 0; i < N; i++) {
        if(host_array[i] != i) {
            error++;
        }
    }

    if(error == 0) {
        printf("Test passed!\n");
    }
    else {
        printf("Test failed, %d errors found.\n", error);
    }

    // Cleanup
    free(host_array);
    acc_free(device_array);

    return 0;
}