#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000
#define VECTOR_LENGTH 128

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform vector addition in parallel
    #pragma acc parallel loop vector_length(VECTOR_LENGTH)
    for (i = 0; i < N; i++) {
        a[i] += b[i];
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (a[i] != (rand() % 100) + (rand() % 100)) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed\n");
    return 0;
}