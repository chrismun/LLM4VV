#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a kernel
    int kernel_id = acc_create_kernel(NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    if (kernel_id == 0) {
        err = 1;
    }

    // Set the wait clause for the kernel
    acc_set_wait_clause(kernel_id, 1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    // Launch the kernel
    acc_launch_kernel(kernel_id, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    // Wait for the kernel to finish
    acc_wait_kernel(kernel_id);

    // Check the result
    if (acc_get_kernel_result(kernel_id) != 0) {
        err = 1;
    }

    // Clean up
    acc_destroy_kernel(kernel_id);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}