#include <iostream>
#include <stdlib.h> // for rand() and srand()
#include <unistd.h> // for sleep(), to simulate delay
#include "acc_testsuite.h"

#ifndef T1
// T1:parallel construct, wait clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Setting up dummy data
    const int size = 1024;
    int* data = new int[size];
    int* results = new int[size];

    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 100; // random initialize
    }

    // Parallel region 1 with dummy operations
    #pragma acc parallel loop copy(data[0:size])
    for (int i = 0; i < size; ++i) {
        data[i] = data[i] * 2; // Dummy computation
    }
    
    // Simulate delay to ensure there's something to wait for
    #pragma acc parallel
    {
        sleep(1); // Artificial delay inside a parallel region
    }
    
    // Parallel region 2 should wait for all previous async operations to complete
    #pragma acc parallel loop copyin(data[0:size]) copyout(results[0:size]) wait
    for (int i = 0; i < size; ++i) {
        results[i] = data[i] + 1; // Another dummy computation that depends on the first
    }
    
    // Verification
    for (int i = 0; i < size; ++i) {
        if (results[i] != data[i] + 1) {
            err++;
        }
    }

    delete[] data;
    delete[] results;

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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}