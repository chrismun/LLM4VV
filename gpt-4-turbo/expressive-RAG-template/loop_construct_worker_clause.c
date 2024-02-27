#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1: loop construct, worker clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // A fixed seed for reproducibility

    const int size = 1000;
    int a[size];

    // Initialize array with zeros
    for (int i = 0; i < size; i++) {
        a[i] = 0;
    }

    // Parallel region using OpenACC
#pragma acc parallel num_workers(4)
    {
#pragma acc loop worker
        for (int i = 0; i < size; i++) {
            a[i] = 1; // Assign 1 to each element to indicate work done on that element
        }
    }

    // Verifying that the array has been updated appropriately
    for (int i = 0; i < size; i++) {
        if (a[i] != 1) {
            err++;
        }
    }

    return err;
}
#endif

// The main execution entry
int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // Here, modified for a single call, adjust as needed.
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}