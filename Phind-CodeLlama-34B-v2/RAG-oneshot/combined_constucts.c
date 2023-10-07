#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024

int main() {
    int i;
    int *a, *b;

    a = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    b = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    for (i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copy(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS])
    {
        #pragma acc parallelloop
        for (i = 0; i < NUM_ELEMENTS; i++) {
            a[i] = a[i] * 2;
        }

        #pragma acc serialloop
        for (i = 0; i < NUM_ELEMENTS; i++) {
            b[i] = a[i] + 1;
        }

        #pragma acc kernels loop
        for (i = 0; i < NUM_ELEMENTS; i++) {
            b[i] = b[i] * 2;
        }
    }

    int errors = 0;
    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (b[i] != (a[i] + 1) * 2) {
            errors++;
        }
    }

    printf("Number of errors: %d\n", errors);

    free(a);
    free(b);

    return 0;
}