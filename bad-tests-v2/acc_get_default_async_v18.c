#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int test_acc_get_default_async(int async) {
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);
    acc_set_device_num(device_type, device_num, async);

    int default_async = acc_get_default_async();
    if (default_async != async) {
        printf("Error: acc_get_default_async() returned %d, expected %d\n", default_async, async);
        err++;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test_acc_get_default_async(x % 2);
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}