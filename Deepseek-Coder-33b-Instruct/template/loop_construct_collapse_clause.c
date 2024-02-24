#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define M 100

int main() {
    int i, j;
    int sum = 0;
    int *a = (int*)malloc(N * M * sizeof(int));

    // Initialize the array
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            a[i*M + j] = i + j;
        }
    }

    // Perform the sum reduction
    #pragma acc parallel loop collapse(2) reduction(+:sum)
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            sum += a[i*M + j];
        }
    }

    printf("Sum: %d\n", sum);

    free(a);

    return 0;
}