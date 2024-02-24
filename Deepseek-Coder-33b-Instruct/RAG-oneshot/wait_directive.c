#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Perform operations on arrays
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels
        for(int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        // Wait for operations to complete
        #pragma acc wait
    }

    // Verify results
    for(int i = 0; i < N; i++) {
        if(c[i] != a[i] + b[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}