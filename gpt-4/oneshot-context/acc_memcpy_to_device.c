#include "openacc.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

int main() {
    int *host_data = (int *) malloc(SIZE * sizeof(int));
    int *device_data = (int *) acc_malloc(SIZE * sizeof(int));
    
    // Initialize host data
    for(int i = 0; i < SIZE; i++){
        host_data[i] = i;
    }

    // Copy data from host to device
    acc_memcpy_to_device(device_data, host_data, SIZE * sizeof(int));

    // Launch a parallel region to check if the data has been correctly copied to the device
    #pragma acc parallel present(device_data[0:SIZE])
    {
        #pragma acc loop
        for(int i = 0; i < SIZE; i++){
            if(device_data[i] != i){
                printf("Error: data at index %d was not copied correctly\n", i);
                exit(1);
            }
        }
    }

    printf("Data was correctly copied to the device.\n");

    // Cleanup
    acc_free(device_data);
    free(host_data);

    return 0;
}