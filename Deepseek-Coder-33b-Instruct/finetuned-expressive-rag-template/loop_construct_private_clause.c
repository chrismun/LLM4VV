#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int i, tmp = 0;

    // Initialize array with random numbers
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Perform parallel reduction
    #pragma acc parallel loop private(tmp)
    for (i = 0; i < N; i++) {
        tmp += a[i];
    }

    // Print the result
    printf("Sum: %d\n", tmp);

    free(a);
    return 0;
}