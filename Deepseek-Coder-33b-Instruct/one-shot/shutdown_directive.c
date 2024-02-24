#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100
#define PRECISION 0.0001

int main() {
    int i;
    double *a, *b;
    a = (double*)malloc(N * sizeof(double));
    b = (double*)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}