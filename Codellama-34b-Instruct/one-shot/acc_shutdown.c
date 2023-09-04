#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_shutdown(void) {
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);
    acc_set_device_num(device_type, device_num, 0);
    acc_shutdown(device_type);
    return err;
}

int main(void) {
    int failcode = 0;
    int failed;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test_acc_shutdown();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }
    return failcode;
}