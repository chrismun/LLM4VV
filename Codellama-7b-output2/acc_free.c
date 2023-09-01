#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory for the data
    int *data = (int *)malloc(sizeof(int) * N);
    if (data == NULL){
        err = 1;
    }

    // Initialize the data
    for (int i = 0; i < N; i++){
        data[i] = i;
    }

    // Create an OpenACC accelerator
    acc_set_device_type(acc_device_type_cpu);
    acc_set_device_num(0);
    acc_set_async(0);
    acc_set_num_gangs(1);
    acc_set_num_workers(1);
    acc_set_vector_length(1);

    // Create an OpenACC kernel
    acc_kernel_t kernel = acc_create_kernel(data, N, 1);
    if (kernel == NULL){
        err = 1;
    }

    // Free the kernel
    acc_free(kernel);

    // Free the data
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