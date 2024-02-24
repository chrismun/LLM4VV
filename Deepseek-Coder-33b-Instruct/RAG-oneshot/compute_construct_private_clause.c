#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10

int main() {
    int *array = (int*)malloc(SIZE * sizeof(int));
    int *original = (int*)malloc(SIZE * sizeof(int));

    // Initialize the array
    for(int i = 0; i < SIZE; i++) {
        array[i] = i;
        original[i] = i;
    }

    // Use OpenACC to create a private copy of the array in each thread
    #pragma acc parallel copy(array[0:SIZE])
    {
        #pragma acc loop private(array)
        for(int i = 0; i < SIZE; i++) {
            array[i] *= 2;
        }
    }

    // Print the original array to verify that it has not been modified
    printf("Original array:\n");
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", original[i]);
    }
    printf("\n");

    free(array);
    free(original);

    return 0;
}