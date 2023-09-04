#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data_host_src and data_dev_dest
    int* data_host_src = (int*)malloc(sizeof(int) * 10);
    int* data_dev_dest = (int*)acc_malloc(sizeof(int) * 10);

    // Fill data_host_src with random values
    for (int i = 0; i < 10; i++) {
        data_host_src[i] = rand();
    }

    // Copy data from data_host_src to data_dev_dest
    acc_memcpy_to_device(data_dev_dest, data_host_src, sizeof(int) * 10);

    // Check if data_dev_dest contains the same values as data_host_src
    for (int i = 0; i < 10; i++) {
        if (data_dev_dest[i] != data_host_src[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(data_host_src);
    acc_free(data_dev_dest);

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