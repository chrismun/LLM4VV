#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000

int main() {
    int i, sum = 0;
    int *a = (int*)malloc(N * sizeof(int));

    // Initialize array with random numbers
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Perform parallel reduction using OpenACC tile clause
    #pragma acc parallel loop copy(sum)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("Sum: %d\n", sum);

    free(a);

    return 0;
}