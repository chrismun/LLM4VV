#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    int a[10];
    int b[10];

    #pragma acc parallel copyin(a)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            a[i] = i;
        }
    }

    #pragma acc parallel copyin(b)
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            b[i] = a[i];
        }
    }

    if (memcmp(a, b, sizeof(a)) != 0) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel
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