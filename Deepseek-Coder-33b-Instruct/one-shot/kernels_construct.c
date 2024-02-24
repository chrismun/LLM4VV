#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define N 1000
#define PRECISION 0.001

int main() {
    int i;
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));
    double *c = (double*)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (fabs(c[i] - (a[i] + b[i])) > PRECISION) {
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}