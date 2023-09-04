#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc atomic
    {
        int x = 0;
        x++;
        if (x != 1) {
            err = 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel loop
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}