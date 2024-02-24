#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int *data_copy = (int*)malloc(SIZE * sizeof(int));

    // Initialize data
    for(int i = 0; i < SIZE; i++) {
        data[i] = i;
        data_copy[i] = 0;
    }

    // Copy data to device
    #pragma acc data copyin(data[0:SIZE])
    {
        // Update data in device memory
        #pragma acc update device(data[0:SIZE])

        // Update data in local memory
        #pragma acc update self(data[0:SIZE])
    }

    // Verify the update
    int error = 0;
    for(int i = 0; i < SIZE; i++) {
        if(data[i] != data_copy[i]) {
            error = 1;
            break;
        }
    }

    if(error) {
        printf("Update failed!\n");
    } else {
        printf("Update succeeded!\n");
    }

    free(data);
    free(data_copy);

    return 0;
}