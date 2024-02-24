#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define PRECISION 0.0001

int main() {
    int i;
    double *a, *b;
    a = (double*)malloc(N * sizeof(double));
    b = (double*)malloc(N * sizeof(double));

    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for(i = 0; i < N; i++) {
        if(fabs(b[i] - a[i]) > PRECISION) {
            printf("Error: b[%d] = %f, a[%d] = %f\n", i, b[i], i, a[i]);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}