#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 123456789

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_gangs(2)
    {
        #pragma acc loop gang
        for (int i = 0; i < 10; i++) {
            #pragma acc loop gang
            for (int j = 0; j < 10; j++) {
                if (i == j) {
                    err = 1;
                }
            }
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}