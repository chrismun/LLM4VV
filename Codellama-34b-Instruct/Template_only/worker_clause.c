#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a worker thread
    int worker_id = acc_create_worker();
    if (worker_id == -1) {
        err = 1;
    }

    // Set the worker thread to run the kernel
    acc_set_worker_kernel(worker_id, kernel);

    // Launch the worker thread
    acc_launch_worker(worker_id);

    // Wait for the worker thread to complete
    acc_wait_worker(worker_id);

    // Check the result of the kernel
    if (acc_get_kernel_result(worker_id) != 0) {
        err = 1;
    }

    // Destroy the worker thread
    acc_destroy_worker(worker_id);

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