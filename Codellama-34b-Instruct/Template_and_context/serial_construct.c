#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc serial
    {
        // Serial code goes here
        printf("Hello from the serial region!\n");
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel
    {
        failed = 0;
        for (int x = 0; x < NUM_TEST_CALLS; ++x) {
            failed = failed + test1();
        }
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}