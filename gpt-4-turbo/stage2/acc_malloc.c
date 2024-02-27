#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    const size_t bytes = 1024; // Number of bytes to allocate.
    int* device_ptr;

    // Using acc_malloc to allocate memory on the device.
    device_ptr = (int*)acc_malloc(bytes);
    
    // Check if the allocation failed.
    if (device_ptr == NULL) {
        printf("Allocation failure: acc_malloc returned NULL.\n");
        return ++err;
    }
    
    // Check if the allocated memory is present on the device.
    if (!acc_is_present(device_ptr, bytes)) {
        printf("Error: allocated memory is not present on the device.\n");
        acc_free(device_ptr); // Cleanup.
        return ++err;
    }

    // Free the allocated memory.
    acc_free(device_ptr);
    
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