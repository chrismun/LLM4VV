#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a kernel
    acc_kernel kernel;
    kernel.name = "my_kernel";
    kernel.num_args = 1;
    kernel.args[0] = data;
    kernel.num_threads = 10;
    kernel.num_blocks = 1;
    kernel.shared_memory_size = 0;
    kernel.grid_size = 10;
    kernel.block_size = 1;
    kernel.device_type = ACC_DEVICE_TYPE_GPU;
    kernel.device_id = 0;

    // Launch the kernel
    acc_launch_kernel(kernel);

    // Verify the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Free data
    free(data);

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