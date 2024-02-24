#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *array = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize array with random numbers
    for (i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    // Use OpenACC to cache the array
    #pragma acc data copy(array[0:SIZE])
    {
        #pragma acc parallel loop
        for (i = 0; i < SIZE; i++) {
            #pragma acc cache(array[i])
            {
                // Do some computation with array[i]
                array[i] = array[i] * 2;
            }
        }
    }

    // Print the array to verify the cache directive
    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }

    free(array);
    return 0;
}