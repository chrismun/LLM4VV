#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Perform computation on GPU
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        // Wait for GPU computation to complete
        #pragma acc wait
    }

    // Verify results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All results are correct!\n");
    return 0;
}