#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize the data
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop vector
    for(i = 0; i < SIZE; i++) {
        data[i] = data[i] * 2;
    }

    // Verify the results
    for(i = 0; i < SIZE; i++) {
        if(data[i] != i * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}