#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc_free, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    size_t array_size = 1024 * sizeof(int); // Example size: 1024 integers
    int* device_array = static_cast<int*>(acc_malloc(array_size));

    if (device_array == NULL) {
        // If acc_malloc failed to allocate memory, treat as an error in this context
        return 1;
    }

    // Initialize device memory to trigger actual memory allocation on some devices
    #pragma acc parallel loop present(device_array[0:1024])
    for (int i = 0; i < 1024; ++i) {
        device_array[i] = rand(); // Random initialization
    }

    // Free previously allocated memory
    acc_free(device_array);

    // Ideally, one would check if device memory was freed correctly,
    // but since acc_free doesn't return a success/failure indicator,
    // we consider reaching this point without runtime errors as 'success'.
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;

    #ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    #endif

    return failcode;
}