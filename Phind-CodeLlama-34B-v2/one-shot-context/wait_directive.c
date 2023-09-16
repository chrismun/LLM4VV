#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int i;
    double *a, *b;

    a = (double *) malloc(N * sizeof(double));
    b = (double *) malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc data copy(a[0:N], b[0:N])
    {
        #pragma acc kernels async(1)
        {
            for (i = 0; i < N; i++) {
                b[i] = a[i] * 2.0;
            }
        }

        #pragma acc wait(1)

        for (i = 0; i < N; i++) {
            if (b[i] != a[i] * 2.0) {
                printf("Test failed: b[%d] = %f, expected %f\n", i, b[i], a[i] * 2.0);
                return 1;
            }
        }
    }

    printf("Test passed\n");
    return 0;
}