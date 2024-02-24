#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

int main() {
    int i, j;
    int *a = (int*)malloc(N * N * sizeof(int));
    int *b = (int*)malloc(N * N * sizeof(int));

    // Initialize the arrays
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            a[i*N + j] = i*N + j;
            b[i*N + j] = 0;
        }
    }

    // Use OpenACC to copy the data to the device and collapse the loops
    #pragma acc data copyin(a[0:N*N]) copyout(b[0:N*N])
    {
        #pragma acc parallel loop collapse(2)
        for(i = 0; i < N; i++) {
            for(j = 0; j < N; j++) {
                b[i*N + j] = a[i*N + j];
            }
        }
    }

    // Verify the results
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(b[i*N + j] != a[i*N + j]) {
                printf("Verification failed at index (%d, %d)\n", i, j);
                return 1;
            }
        }
    }

    printf("Verification passed\n");
    return 0;
}