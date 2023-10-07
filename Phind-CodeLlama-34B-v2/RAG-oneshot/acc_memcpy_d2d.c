#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 0.0001

int main() {
    int i;
    int fail = 0;
    real_t *a, *b, *c;

    a = (real_t *)malloc(NUM_ELEMENTS * sizeof(real_t));
    b = (real_t *)malloc(NUM_ELEMENTS * sizeof(real_t));
    c = (real_t *)malloc(NUM_ELEMENTS * sizeof(real_t));

    for (i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i * 1.0;
        b[i] = 0.0;
        c[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS], c[0:NUM_ELEMENTS])

    #pragma acc kernels present(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS])
    {
        #pragma acc loop
        for (i = 0; i < NUM_ELEMENTS; i++) {
            b[i] = a[i];
        }
    }

    #pragma acc kernels present(b[0:NUM_ELEMENTS], c[0:NUM_ELEMENTS])
    {
        #pragma acc loop
        for (i = 0; i < NUM_ELEMENTS; i++) {
            c[i] = b[i];
        }
    }

    #pragma acc exit data copyout(c[0:NUM_ELEMENTS])

    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (fabs(c[i] - a[i]) > PRECISION) {
            fail++;
        }
    }

    printf("Test passed: %s\n", (fail == 0) ? "Yes" : "No");

    free(a);
    free(b);
    free(c);

    return 0;
}