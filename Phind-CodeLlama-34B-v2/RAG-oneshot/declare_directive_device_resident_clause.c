#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int i;
    double *a, *b;

    a = (double *)malloc(N * sizeof(double));
    b = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc declare create(a[0:N]) device_resident

    #pragma acc data copy(b[0:N])
    {
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (i = 0; i < N; i++) {
        if (fabs(b[i] - a[i]) > 1e-10) {
            printf("Test failed at index %d: %f != %f\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}