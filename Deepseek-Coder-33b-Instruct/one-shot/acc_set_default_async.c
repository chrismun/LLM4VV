#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int sum = 0;

    // Initialize data
    for(int i = 0; i < SIZE; i++) {
        data[i] = i + 1;
    }

    // Set default async behavior
    acc_set_default_async(1);

    // Perform parallel sum reduction
    #pragma acc parallel loop copy(sum) async
    for(int i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    // Wait for all kernels to finish
    #pragma acc wait

    // Print the result
    printf("Sum: %d\n", sum);

    free(data);
    return 0;
}