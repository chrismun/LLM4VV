#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    int *A = (int *)malloc(sizeof(int) * 10);
    int *B = (int *)malloc(sizeof(int) * 10);
    int *C = (int *)malloc(sizeof(int) * 10);

    #pragma acc parallel device_resident(A, B, C)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            A[i] = i;
            B[i] = i * 2;
            C[i] = i * 3;
        }
    }

    #pragma acc parallel device_resident(A, B, C)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            if (A[i] != i || B[i] != i * 2 || C[i] != i * 3) {
                err = 1;
            }
        }
    }

    free(A);
    free(B);
    free(C);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel device_resident(A, B, C)
    {
        #pragma acc loop
        for (int x = 0; x < NUM_TEST_CALLS; x++) {
            failed = failed + test1();
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}