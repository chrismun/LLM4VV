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

    // Copy data to device using enter data directive
    #pragma acc data copyin(host_data[0:SIZE]) copyout(device_data[0:SIZE])
    {
        #pragma acc enter data copyin(host_data[0:SIZE]) create(device_data[0:SIZE])
        {
            // Copy data from host to device
            #pragma acc update device(device_data[0:SIZE])
        }
    }

    // Verify the data
    for(int i = 0; i < SIZE; i++) {
        if(host_data[i] != device_data[i]) {
            printf("Data verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Data verification passed\n");
    return 0;
}