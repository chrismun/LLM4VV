#include "acc_testsuite.h"

int test_set_default_async() {
    int err = 0;
    int old_default_async = acc_get_default_async();

    #pragma acc set default_async(10)

    int new_default_async = acc_get_default_async();
    if (new_default_async != 10) {
        err += 1;
    }

    #pragma acc set default_async(acc_async_default)

    int restored_default_async = acc_get_default_async();
    if (restored_default_async != old_default_async) {
        err += 1;
    }

    return err;
}

int test_set_device_num() {
    int err = 0;
    int old_device_num = acc_get_device_num();

    #pragma acc set device_num(1)

    int new_device_num = acc_get_device_num();
    if (new_device_num != 1) {
        err += 1;
    }

    #pragma acc set device_num(-1)

    int restored_device_num = acc_get_device_num();
    if (restored_device_num != old_device_num) {
        err += 1;
    }

    return err;
}

int test_set_device_type() {
    int err = 0;
    acc_device_t old_device_type = acc_get_device_type();

    #pragma acc set device_type(acc_device_nvidia)

    acc_device_t new_device_type = acc_get_device_type();
    if (new_device_type != acc_device_nvidia) {
        err += 1;
    }

    #pragma acc set device_type(0)

    acc_device_t restored_device_type = acc_get_device_type();
    if (restored_device_type != old_device_type) {
        err += 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    failed = test_set_default_async();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    failed = test_set_device_num();
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    failed = test_set_device_type();
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    return failcode;
}