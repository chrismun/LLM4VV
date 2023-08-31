#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    int a = 0;
    int b = 0;

    #pragma acc parallel num_threads(2) private(a)
    {
        a = rand();
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            b = a + i;
        }
    }

    if (b != (a + 10)) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    #pragma acc parallel num_threads(2)
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