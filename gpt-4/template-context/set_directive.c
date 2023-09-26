#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

// Test Default Async
int test_default_async() {
    int err = 0;
    
    // Set default async
    #pragma acc set default_async(2)
    acc_init(acc_device_default);
    int default_async = acc_get_default_async();
    
    if (default_async != 2) {
        printf("Async: Expected %d, got %d\n", 2, default_async);
        err = 1;
    }
    acc_shutdown(acc_device_default);

    return err;
}

// Test Device Num
int test_device_num() {
    int err = 0;

    // Assuming we have at least two devices
    #pragma acc set device_num(1)
    acc_init(acc_device_default);
    int device_num = acc_get_device_num(acc_device_default);

    if (device_num != 1) {
        printf("Device Number: Expected %d, got %d\n", 1, device_num);
        err = 1;
    }
    acc_shutdown(acc_device_default);

    return err;
}

// Test Device Type
int test_device_type() {
    int err = 0;

    // Assuming we have a GPU
    #pragma acc set device_type(acc_device_nvidia)
    acc_init(acc_device_nvidia);
    acc_device_t device_type = acc_get_device_type();

    if (device_type != acc_device_nvidia) {
        printf("Device Type: Expected %d, got %d\n", acc_device_nvidia, device_type);
        err = 1;
    }
    acc_shutdown(acc_device_nvidia);

    return err;
}

int main() {
    srand(SEED);
    int failcode = 0;

    int failed = test_default_async();
    failcode += (failed != 0) ? 1 << 0 : 0;

    failed = test_device_num();
    failcode += (failed != 0) ? 1 << 1 : 0;

    failed = test_device_type();
    failcode += (failed != 0) ? 1 << 2 : 0;

    return failcode;
}