#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random value for the default async value
    int default_async = rand() % 10;

    // Set the default async value to the generated value
    acc_set_default_async(default_async);

    // Get the default async value and compare it to the generated value
    int actual_default_async = acc_get_default_async();
    if (actual_default_async != default_async) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}