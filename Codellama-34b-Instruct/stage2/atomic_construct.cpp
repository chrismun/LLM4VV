#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Test atomic read
    int x = rand();
    int y = x;
    #pragma acc atomic read
    x = x + 1;
    if (x != y + 1) {
        err = 1;
    }

    // Test atomic write
    x = rand();
    y = x;
    #pragma acc atomic write
    x = x + 1;
    if (x != y + 1) {
        err = 1;
    }

    // Test atomic update
    x = rand();
    y = x;
    #pragma acc atomic update
    x = x + 1;
    if (x != y + 1) {
        err = 1;
    }

    // Test atomic capture
    x = rand();
    y = x;
    #pragma acc atomic capture
    x = x + 1;
    if (x != y + 1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}