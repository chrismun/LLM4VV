#include "acc_testsuite.h"
#include <cstdlib>
#include <openacc.h>

#ifndef T1
/*T1:acc malloc,V:2.0-2.7*/
int test1() {
    int err = 0;
    size_t size = 128; // Size of memory to be allocated 

    void* devicePtr = acc_malloc(size);
    
    // Verify that memory allocation was successful
    if (devicePtr == NULL) {
        err = 1;
    }

    // Make sure to free the memory when finished
    acc_free(devicePtr);
    
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