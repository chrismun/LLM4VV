#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACC_DEFAULT_ASYNC_VAR 0
#define ACC_DEVICE_NUM_VAR 1
#define ACC_DEVICE_TYPE_VAR 2

#define ACC_ASYNC_DEFAULT 0
#define ACC_ASYNC_SYNC 1
#define ACC_ASYNC_NONE 2

#define ACC_DEVICE_TYPE_CPU 0
#define ACC_DEVICE_TYPE_GPU 1
#define ACC_DEVICE_TYPE_ACCELERATOR 2

#define ACC_DEVICE_NUM_DEFAULT 0

#define ACC_ERROR_DEVICE_TYPE_UNAVAILABLE 1
#define ACC_ERROR_DEVICE_UNAVAILABLE 2
#define ACC_ERROR_INVALID_ASYNC 3

#define ACC_SUCCESS 0

int acc_set_default_async(int async) {
    if (async == ACC_ASYNC_DEFAULT) {
        ACC_DEFAULT_ASYNC_VAR = ACC_ASYNC_DEFAULT;
    } else if (async == ACC_ASYNC_SYNC) {
        ACC_DEFAULT_ASYNC_VAR = ACC_ASYNC_SYNC;
    } else if (async == ACC_ASYNC_NONE) {
        ACC_DEFAULT_ASYNC_VAR = ACC_ASYNC_NONE;
    } else {
        return ACC_ERROR_INVALID_ASYNC;
    }
    return ACC_SUCCESS;
}

int acc_set_device_num(int device_num) {
    if (device_num < 0) {
        return ACC_ERROR_DEVICE_UNAVAILABLE;
    }
    ACC_DEVICE_NUM_VAR = device_num;
    return ACC_SUCCESS;
}

int acc_set_device_type(int device_type) {
    if (device_type < 0 || device_type > ACC_DEVICE_TYPE_ACCELERATOR) {
        return ACC_ERROR_DEVICE_TYPE_UNAVAILABLE;
    }
    ACC_DEVICE_TYPE_VAR = device_type;
    return ACC_SUCCESS;
}

int main() {
    int async = ACC_ASYNC_DEFAULT;
    int device_num = ACC_DEVICE_NUM_DEFAULT;
    int device_type = ACC_DEVICE_TYPE_CPU;

    // Set default async
    acc_set_default_async(async);

    // Set device num
    acc_set_device_num(device_num);

    // Set device type
    acc_set_device_type(device_type);

    return 0;
}