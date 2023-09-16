#include "acc_testsuite.h"
#include <stddef.h>

// T1: acc get default async, V: 2.7-3.3
int test1() {
    int err = 0;
    int default_async_val = rand() % 100; // assign some random value
    acc_set_default_async(default_async_val);

    // Get the default async value using OpenACC API
    int retrieved_async_val = acc_get_default_async();

    // Check if retrieved async value is same as the one set above
    if (retrieved_async_val != default_async_val) {
        err = 1;
    }

    return err;
}

int main() {
    srand(SEED);
    int failcode = 0;

    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + 1;
    }

    return failcode;
}