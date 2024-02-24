#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize the data array
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Update the data array using acc update self
    #pragma acc data copy(data[0:SIZE])
    {
        #pragma acc update self(data[0:SIZE])
    }

    // Check if the data array has been correctly updated
    for(i = 0; i < SIZE; i++) {
        if(data[i] != i) {
            printf("Error: data[%d] is %d, expected %d\n", i, data[i], i);
            return 1;
        }
    }

    printf("Success: data array has been correctly updated\n");
    return 0;
}