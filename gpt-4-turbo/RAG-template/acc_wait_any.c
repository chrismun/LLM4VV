#include "acc_testsuite.h"
#ifndef T1
// T1:{feature},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Example setup - normally, you'd create some real asynchronous operations
    int count = 2; // Example count of async queues
    int wait_arg[2];
    wait_arg[0] = 1; // Assumed identifiers for async queues
    wait_arg[1] = 2; 

    #pragma acc data copy(err)
    {
        // Launching dummy operations in different async queues
        #pragma acc parallel async(wait_arg[0])
        {
            // Dummy operation for demonstration
        }
        
        #pragma acc parallel async(wait_arg[1])
        {
            // Another dummy operation
        }

        // Using acc_wait_any to wait for any of the above operations to complete
        int completed_queue = acc_wait_any(count, wait_arg);
        
        if (completed_queue < 0 || completed_queue >= count) {
            err = 1; // Should be within range [0, count)
        } 
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}