#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Generate random data
    int data[N];
    for (int i = 0; i < N; i++){
        data[i] = rand();
    }

    // Create an array of pointers to the data
    int *data_ptr[N];
    for (int i = 0; i < N; i++){
        data_ptr[i] = &data[i];
    }

    // Create an OpenACC data clause
    acc_data_t data_clause;
    data_clause.num_data = N;
    data_clause.data_ptr = data_ptr;

    // Create an OpenACC kernel
    acc_kernel_t kernel;
    kernel.num_data = N;
    kernel.data_ptr = data_ptr;

    // Execute the kernel
    acc_exec_kernel(kernel);

    // Check that the data has been modified correctly
    for (int i = 0; i < N; i++){
        if (data[i] != kernel.data_ptr[i]){
            err = 1;
        }
    }

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