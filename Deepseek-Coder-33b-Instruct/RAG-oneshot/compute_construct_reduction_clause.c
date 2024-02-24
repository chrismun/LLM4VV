#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int i;
    int sum = 0;
    int *data = (int*)malloc(SIZE * sizeof(int));

    // Initialize the data
    for(i = 0; i < SIZE; i++) {
        data[i] = i + 1;
    }

    // Compute the sum of the array using OpenACC
    #pragma acc parallel loop reduction(+:sum)
    for(i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    // Print the result
    printf("Sum: %d\n", sum);

    free(data);
    return 0;
}