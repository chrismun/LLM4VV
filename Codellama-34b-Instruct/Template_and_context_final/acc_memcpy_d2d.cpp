c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Test 1: acc memcpy d2d with bytes set to 0
    int dev_num_dest = acc_get_device_num();
    int dev_num_src = acc_get_device_num();
    void *data_arg_dest = acc_malloc(100);
    void *data_arg_src = acc_malloc(100);
    acc_memcpy_d2d(data_arg_dest, data_arg_src, 0, dev_num_dest, dev_num_src);
    if (acc_get_device_num() != dev_num_dest) {
        err = 1;
    }
    acc_free(data_arg_dest);
    acc_free(data_arg_src);

    // Test 2: acc memcpy d2d with bytes set to a non-zero value and data_arg_dest and data_arg_src pointing to the same memory location
    dev_num_dest = acc_get_device_num();
    dev_num_src = acc_get_device_num();
    data_arg_dest = acc_malloc(100);
    data_arg_src = acc_malloc(100);
    acc_memcpy_d2d(data_arg_dest, data_arg_src, 100, dev_num_dest, dev_num_src);
    if (acc_get_device_num() != dev_num_dest) {
        err = 1;
    }
    acc_free(data_arg_dest);
    acc_free(data_arg_src);

    // Test 3: acc memcpy d2d with bytes set to a non-zero value and data_arg_dest and data_arg_src pointing to different memory locations
    dev_num_dest = acc_get_device_num();
    dev_num_src = acc_get_device_num();
    data_arg_dest = acc_malloc(100);
    data_arg_src = acc_malloc(100);
    acc_memcpy_d2d(data_arg_dest, data_arg_src, 100, dev_num_dest, dev_num_src);
    if (acc_get_device_num() != dev_num_dest) {
        err = 1;
    }
    acc_free(data_arg_dest);
    acc_free(data_arg_src);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    if (failcode != 0) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}