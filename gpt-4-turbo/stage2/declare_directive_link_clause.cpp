#include <iostream>
#include <cstdlib>

// Assuming acc_testsuite.h defines necessary test suite configurations
// #include "acc_testsuite.h"

#ifndef T1
// T1:declare directive link clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL)); // Using time as seed for randomness

    // Global variable for testing the link clause
    static int globalVar = 0;

#pragma acc declare link(globalVar)

    // Change value of globalVar within an OpenACC region
#pragma acc parallel
    {
#pragma acc loop
        for (int i = 0; i < 1; ++i) { // Loop to simulate parallel workload
            globalVar = rand() % 100; // Assigning a random value between 0 and 99
        }
    }

    // Check if globalVar is changed, indicating it was correctly linked
    if (globalVar == 0) { // Value unchanged if link failed
        err = 1; // Indicate an error
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // Assuming NUM_TEST_CALLS is simulated by a single call here
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}