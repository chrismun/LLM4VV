c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Test 1: acc_memcpy_d2d with bytes set to 0
    int dev_num_dest = 0;
    int dev_num_src = 0;
    void *data_arg_dest = NULL;
    void *data_arg_src = NULL;
    size_t bytes = 0;
    acc_memcpy_d2d(data_arg_dest, data_arg_src, bytes, dev_num_dest, dev_num_src);
    if (data_arg_dest != NULL || data_arg_src != NULL) {
        err = 1;
    }

    // Test 2: acc_memcpy_d2d with bytes set to a non-zero value and data_arg_dest and data_arg_src pointing to the same memory location
    dev_num_dest = 0;
    dev_num_src = 0;
    data_arg_dest = malloc(100);
    data_arg_src = data_arg_dest;
    bytes = 100;
    acc_memcpy_d2d(data_arg_dest, data_arg_src, bytes, dev_num_dest, dev_num_src);
    if (data_arg_dest != data_arg_src) {
        err = 1;
    }

    // Test 3: acc_memcpy_d2d with bytes set to a non-zero value and data_arg_dest and data_arg_src pointing to different memory locations
    dev_num_dest = 0;
    dev_num_src = 0;
    data_arg_dest = malloc(100);
    data_arg_src = malloc(100);
    bytes = 100;
    acc_memcpy_d2d(data_arg_dest, data_arg_src, bytes, dev_num_dest, dev_num_src);
    if (data_arg_dest == data_arg_src) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}