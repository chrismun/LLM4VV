#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = NULL;

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Allocate device memory
    device_array = (int*)acc_malloc(N * sizeof(int));

    // Copy data to device
    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        #pragma acc kernels
        for(int i = 0; i < N; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Verify if_present clause
    for(int i = 0; i < N; i++) {
        if(device_array[i] != host_array[i]) {
            printf("Error: if_present clause not working as expected\n");
            return 1;
        }
    }

    printf("if_present clause working as expected\n");

    // Free memory
    free(host_array);
    acc_free(device_array);

    return 0;
}