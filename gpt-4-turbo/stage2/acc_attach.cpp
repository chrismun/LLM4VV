#include <iostream>
#include <openacc.h>
#include <cstdlib>

// Define constants for test simplicity
const int DATA_SIZE = 1024;
const int NUM_TEST_CALLS = 10;
const unsigned SEED = 42;

#ifndef T1
// T1:acc_attach,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // 1. Allocate memory
    int* h_array = new int[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; ++i) {
        h_array[i] = i;  // Initialize array
    }
    
    // 2. Attach operation
    acc_attach((void**)&h_array);

    // 3. Kernel Execution - Mark data to be present on the device
    #pragma acc parallel loop present(h_array)
    for (int i = 0; i < DATA_SIZE; ++i) {
        h_array[i] = h_array[i] * 2;  // Sample operation
    }

    // 4. Detach operation
    acc_detach((void**)&h_array);
    
    // 5. Verification
    for (int i = 0; i < DATA_SIZE; ++i) {
        if (h_array[i] != i * 2) {  // Verify operation result
            err = 1;  // Error detected
            break;
        }
    }

    // Cleanup
    delete[] h_array;

    return err;
}
#endif

int main() {
    int failcode = 0;

#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}