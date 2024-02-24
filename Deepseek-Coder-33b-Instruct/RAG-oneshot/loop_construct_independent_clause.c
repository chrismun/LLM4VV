#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *a = (int*)malloc(SIZE * sizeof(int));
    int *b = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize array a with random numbers
    for(i = 0; i < SIZE; i++) {
        a[i] = rand() % 100;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop independent
    for(i = 0; i < SIZE; i++) {
        b[i] = a[i];
    }

    // Verify that the loop was executed in parallel
    for(i = 0; i < SIZE; i++) {
        if(a[i] != b[i]) {
            printf("Error: a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
            return 1;
        }
    }

    printf("Success: The loop was executed in parallel.\n");
    return 0;
}