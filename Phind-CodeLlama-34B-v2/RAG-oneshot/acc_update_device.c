#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define SEED 123
#define PRECISION 0.001

int validate_acc_update_device_and_self() {
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    int *b = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    for (int x = 0; x < NUM_ELEMENTS; ++x) {
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:NUM_ELEMENTS])
    #pragma acc enter data create(b[0:NUM_ELEMENTS])

    #pragma acc kernels present(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS])
    {
        #pragma acc loop
        for (int x = 0; x < NUM_ELEMENTS; ++x) {
            b[x] = a[x];
        }
    }

    #pragma acc update self(b[0:NUM_ELEMENTS])

    for (int x = 0; x < NUM_ELEMENTS; ++x) {
        if (b[x] != a[x]) {
            err += 1;
        }
    }

    #pragma acc update device(a[0:NUM_ELEMENTS])

    #pragma acc kernels present(a[0:NUM_ELEMENTS], b[0:NUM_ELEMENTS])
    {
        #pragma acc loop
        for (int x = 0; x < NUM_ELEMENTS; ++x) {
            b[x] = a[x];
        }
    }

    #pragma acc update self(b[0:NUM_ELEMENTS])

    for (int x = 0; x < NUM_ELEMENTS; ++x) {
        if (b[x] != a[x]) {
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:NUM_ELEMENTS])
    #pragma acc exit data delete(b[0:NUM_ELEMENTS])

    free(a);
    free(b);

    return err;
}

int main() {
    int failed = validate_acc_update_device_and_self();

    if (failed != 0) {
        printf("Validation failed with %d errors\n", failed);
        return 1;
    } else {
        printf("Validation passed\n");
        return 0;
    }
}