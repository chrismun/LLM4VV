#include <iostream>
#include <cstdlib>
#include <cstring>

#include "acc_testsuite.h"

// T1: acc wait any, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Create an array of async-arguments
    int count = 10;
    int wait_arg[count];
    for (int i = 0; i < count; i++) {
        wait_arg[i] = acc_async_sync;
    }

    // Wait for any of the async-arguments to complete
    int index = acc_wait_any(count, wait_arg);

    // Check if any of the async-arguments completed
    if (index == -1) {
        std::cout << "No async-arguments completed" << std::endl;
    } else {
        std::cout << "Async-argument " << index << " completed" << std::endl;
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