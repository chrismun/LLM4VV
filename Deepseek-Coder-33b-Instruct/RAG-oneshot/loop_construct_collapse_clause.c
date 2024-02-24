#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, j;
    int a[N][N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = 0;
        }
    }

    // Use the collapse clause to parallelize the loop
    #pragma acc parallel loop collapse(2)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
        }
    }

    // Check the result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (a[i][j] != i + j) {
                printf("Error at a[%d][%d]: expected %d, got %d\n", i, j, i + j, a[i][j]);
                return 1;
            }
        }
    }

    printf("Test passed\n");
    return 0;
}