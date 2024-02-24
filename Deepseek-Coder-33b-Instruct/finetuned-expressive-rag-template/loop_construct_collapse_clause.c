#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, j, k;
    int *a = (int*)malloc(N * N * N * sizeof(int));

    // Initialize the array
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                a[i*N*N + j*N + k] = i + j + k;
            }
        }
    }

    // Use OpenACC to collapse the loops
    #pragma acc data copy(a[0:N*N*N])
    {
        #pragma acc parallel loop collapse(3)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (k = 0; k < N; k++) {
                    a[i*N*N + j*N + k] *= 2;
                }
            }
        }
    }

    // Check the result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                if (a[i*N*N + j*N + k] != (i + j + k) * 2) {
                    printf("Error at (%d, %d, %d)\n", i, j, k);
                    return 1;
                }
            }
        }
    }

    printf("All tests passed.\n");
    return 0;
}