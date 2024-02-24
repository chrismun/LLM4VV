#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize array a
    for(int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Create clause
    #pragma acc data copyin(a[0:N]) create(b[0:N])
    {
        #pragma acc kernels
        for(int i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Verify the result
    for(int i = 0; i < N; i++) {
        if(b[i] != a[i]) {
            printf("Error at index %d: b[%d] = %d, a[%d] = %d\n", i, i, b[i], i, a[i]);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}