#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc serial
    {
        // Do some work here
        int x = rand();
        int y = rand();
        int z = x + y;
        if (z != x + y) {
            err = 1;
        }
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