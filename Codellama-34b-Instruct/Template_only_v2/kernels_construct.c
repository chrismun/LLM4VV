#include "acc_testsuite.h"

// T1:kernels construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a kernel
    acc_kernel kernel;
    kernel.name = "my_kernel";
    kernel.num_threads = 1;
    kernel.num_blocks = 1;
    kernel.shared_memory_size = 0;
    kernel.stream = NULL;

    // Launch the kernel
    acc_launch_kernel(kernel);

    // Check that the kernel was launched successfully
    if (acc_get_last_error() != ACC_SUCCESS){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}