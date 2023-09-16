#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 0.0001

int main() {
    int i;
    int fail = 0;
    real_t *a = (real_t *)malloc(NUM_ELEMENTS * sizeof(real_t));
    real_t *b = (real_t *)malloc(NUM_ELEMENTS * sizeof(real_t));

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

    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            fail++;
        }
    }

    if (fail) {
        printf("Test failed: %d elements do not match\n", fail);
    } else {
        printf("Test passed\n");
    }

    free(a);
    free(b);

    return 0;
}