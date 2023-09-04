#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    int x = rand();
    int y = rand();
    int z = rand();

    #pragma acc atomic
    x = x + y;

    #pragma acc atomic
    y = y + z;

    #pragma acc atomic
    z = z + x;

    if (x != y || y != z || z != x) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    if (failcode) {
        printf("Atomic construct failed\n");
    } else {
        printf("Atomic construct passed\n");
    }

    return failcode;
}