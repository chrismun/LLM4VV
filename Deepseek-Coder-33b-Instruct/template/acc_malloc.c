#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a, *b;
    int i;

    // Allocate memory on the GPU
    a = (int*)acc_malloc(N * sizeof(int));
    b = (int*)acc_malloc(N * sizeof(int));

    // Initialize the arrays
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform a vector addition on the GPU
    #pragma acc parallel loop
    for(i = 0; i < N; i++) {
        a[i] += b[i];
    }

    // Print the result
    for(i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    // Free the memory
    acc_free(a);
    acc_free(b);

    return 0;
}