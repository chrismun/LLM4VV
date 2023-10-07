#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 0.001

int main() {
    int i;
    double *a, *b;

    a = (double *) malloc(NUM_ELEMENTS * sizeof(double));
    b = (double *) malloc(NUM_ELEMENTS * sizeof(double));

    for (i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i * 1.0;
        b[i] = 0.0;
    }

    #pragma acc data copyin(a[0:NUM_ELEMENTS]) copyout(b[0:NUM_ELEMENTS])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (i = 0; i < NUM_ELEMENTS; i++) {
                b[i] = a[i];
            }
        }
    }

    int error = 0;
    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (fabs(a[i] - b[i]) > PRECISION) {
            error++;
            printf("Error at index %d: %f != %f\n", i, a[i], b[i]);
        }
    }

    if (error == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed with %d errors.\n", error);
    }

    free(a);
    free(b);

    return 0;
}