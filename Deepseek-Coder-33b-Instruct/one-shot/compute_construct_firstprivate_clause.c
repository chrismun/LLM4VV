#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10

int main() {
    int *array = (int*)malloc(SIZE * sizeof(int));
    int *original = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize the array
    for (i = 0; i < SIZE; i++) {
        array[i] = i;
        original[i] = i;
    }

    // Use OpenACC to modify the array in parallel
    #pragma acc parallel loop firstprivate(array)
    for (i = 0; i < SIZE; i++) {
        array[i] *= 2;
    }

    // Check that the original array is not modified
    for (i = 0; i < SIZE; i++) {
        if (array[i] != original[i] * 2) {
            printf("Error: array[%d] was modified by the OpenACC code\n", i);
            return 1;
        }
    }

    printf("OpenACC implementation of firstprivate clause verified\n");
    return 0;
}