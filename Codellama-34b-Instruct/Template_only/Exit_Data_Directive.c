#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    // Create an OpenACC data environment
    acc_data_t data_env;
    acc_data_create(&data_env, data, 10, sizeof(int));

    // Create an OpenACC data environment for the exit data
    acc_data_t exit_data_env;
    acc_data_create(&exit_data_env, data, 10, sizeof(int));

    // Set the exit data environment to the data environment
    acc_data_set_exit_data(data_env, exit_data_env);

    // Create an OpenACC kernel to copy the data to the device
    acc_kernel_t kernel;
    acc_kernel_create(&kernel, data_env, 10, sizeof(int));

    // Launch the kernel
    acc_kernel_launch(kernel);

    // Wait for the kernel to complete
    acc_kernel_wait(kernel);

    // Check if the data has been copied to the device
    int* device_data = (int*)acc_data_get_device_ptr(data_env);
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Clean up the OpenACC data environment
    acc_data_destroy(data_env);
    acc_data_destroy(exit_data_env);

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