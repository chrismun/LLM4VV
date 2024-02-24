#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int sum = 0;

    // Initialize the array
    for(int i = 0; i < SIZE; i++) {
        data[i] = i + 1;
    }

    // Compute the sum of the array using OpenACC
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    printf("Sum: %d\n", sum);

    free(data);

    return 0;
}