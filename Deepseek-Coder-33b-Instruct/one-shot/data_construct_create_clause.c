#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define N 100
#define PRECISION 0.001

int main() {
    int i;
    double *a, *b;
    a = (double*)malloc(N * sizeof(double));
    b = (double*)malloc(N * sizeof(double));

    // Initialize a
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Create b
    #pragma acc data copyin(a[0:N]) create(b[0:N])
    {
        #pragma acc kernels
        {
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check if b is created correctly
    for (i = 0; i < N; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            printf("Error: b[%d] = %f, expected %f\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}