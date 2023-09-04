#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a Fortran-style array
    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    // Create an OpenACC data environment
    acc_data_t data;
    acc_data_create(&data, arr, 10, 10, 10);

    // Set the data environment to be executable
    acc_data_set_executable(data, 1);

    // Create a Fortran-style array for the result
    int result[10];

    // Execute a Fortran-style kernel on the data environment
    acc_kernel_exec(data, result, 10, 10, 10);

    // Check the result
    for (int i = 0; i < 10; i++) {
        if (result[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Clean up the data environment
    acc_data_destroy(data);

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