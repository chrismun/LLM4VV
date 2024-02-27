#include <iostream>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct firstprivate clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Defining test variables
    int host_val = rand() % 100; // Random value between 0 and 99
    int result = 0;

    // Memory allocation for result. Allocation on host since we're comparing after kernel execution.
    int* result_ptr = &result;

    // Copying host_val to a device variable inside a kernels region, applying the firstprivate clause
#pragma acc kernels firstprivate(host_val) copy(result_ptr[0:1])
    {
        host_val += 5;  // Modifying the value inside the parallel region
        result_ptr[0] = host_val;  // copying the modified value to result
    }

    // Checking if the host_val has remained unchanged, which would confirm firstprivate works
    if (host_val != result_ptr[0] - 5) {
        err++;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}