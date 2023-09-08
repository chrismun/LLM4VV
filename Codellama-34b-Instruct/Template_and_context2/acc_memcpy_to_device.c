#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int data_host_src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int data_dev_dest[10];

    // Copy data from local memory to device memory
    acc_memcpy_to_device(data_dev_dest, data_host_src, sizeof(data_host_src));

    // Check if data has been correctly copied
    for (int i = 0; i < 10; i++){
        if (data_dev_dest[i] != data_host_src[i]){
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}