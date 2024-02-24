#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *host_data = (int*)malloc(SIZE * sizeof(int));
    int *device_data = (int*)malloc(SIZE * sizeof(int));

    // Initialize host data
    for(int i = 0; i < SIZE; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[0:SIZE]) copyout(device_data[0:SIZE])
    {
        #pragma acc kernels
        {
            #pragma acc loop deviceptr(device_data)
            for(int i = 0; i < SIZE; i++) {
                device_data[i] = host_data[i];
            }
        }
    }

    // Verify data
    for(int i = 0; i < SIZE; i++) {
        if(host_data[i] != device_data[i]) {
            printf("Data verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data verification successful\n");
    return 0;
}