#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize data
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Use OpenACC to distribute work across multiple workers
    #pragma acc parallel loop worker
    for(i = 0; i < SIZE; i++) {
        data[i]++;
    }

    // Verify the results
    for(i = 0; i < SIZE; i++) {
        if(data[i] != i + 1) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}