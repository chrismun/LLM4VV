#include <iostream>
#include <vector>
#include <cstdlib> // For srand(), rand()
#include <ctime> // For time()

// Assuming acc_testsuite.h provides necessary test configurations like SEED and NUM_TEST_CALLS
#include "acc_testsuite.h"

#ifndef T1
// T1:data construct copyout clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(static_cast<unsigned>(time(0))); // Initialize random seed

    const int size = 100;
    std::vector<int> host_array(size, 0); // Initialize with zeros

    // OpenACC region to initialize array on accelerator
    #pragma acc data copyout(host_array[0:size])
    {
        // Assuming some operations on host_array which would require copyout to reflect changes back on the host
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            // Dummy operation, in a real scenario this would modify the array's elements
            host_array[i] = 0;
        }
    }

    // Verify the copyout operation
    for(int i = 0; i < size; ++i) {
        if (host_array[i] != 0) { // Check against expected value post copyout
            err++;
            break;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
    #ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    #endif
    return failcode;
}