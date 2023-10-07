#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int i;
    double *a, *b;

    /* Allocate memory on the host */
    a = (double *) malloc(N * sizeof(double));
    b = (double *) malloc(N * sizeof(double));

    /* Initialize the arrays */
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0.0;
    }

    /* Allocate memory on the device */
    double *d_a, *d_b;
    d_a = (double *) acc_malloc(N * sizeof(double));
    d_b = (double *) acc_malloc(N * sizeof(double));

    /* Copy data from the host to the device */
    acc_memcpy(d_a, a, N * sizeof(double));

    /* Launch the kernel */
    #pragma acc kernels present(d_a[0:N], d_b[0:N])
    {
        #pragma acc loop
        for (i = 0; i < N; i++) {
            d_b[i] = d_a[i] * 2.0;
        }
    }

    /* Copy data back to the host */
    acc_memcpy(b, d_b, N * sizeof(double));

    /* Verify the result */
    for (i = 0; i < N; i++) {
        if (fabs(b[i] - (i * 2.0)) > 1e-10) {
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}