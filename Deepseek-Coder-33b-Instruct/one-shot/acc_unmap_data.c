#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int *data_dev = NULL;
    int i;

    // Initialize data
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Map data to the device
    #pragma acc data copyin(data[0:SIZE])
    {
        // Unmap data from the device
        #pragma acc unmap(data)

        // Check if data is still accessible
        for(i = 0; i < SIZE; i++) {
            if(data[i] != i) {
                printf("Data is not accessible after unmap\n");
                return 1;
            }
        }
    }

    printf("Data is accessible after unmap\n");
    return 0;
}