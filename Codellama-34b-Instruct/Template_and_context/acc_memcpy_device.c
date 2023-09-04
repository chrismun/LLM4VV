#include <stdlib.h>
#include <string.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

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

void acc_memcpy_device(d_void *data_dev_dest, d_void *data_dev_src, size_t bytes) {
    if (bytes == 0) {
        return;
    }

    if (data_dev_dest == data_dev_src) {
        return;
    }

    if (data_dev_dest == NULL || data_dev_src == NULL) {
        acc_error("acc_memcpy_device: Invalid null pointer");
        return;
    }

    if (bytes > acc_get_device_memory_size(data_dev_dest)) {
        acc_error("acc_memcpy_device: Invalid memory size");
        return;
    }

    if (bytes > acc_get_device_memory_size(data_dev_src)) {
        acc_error("acc_memcpy_device: Invalid memory size");
        return;
    }

    memcpy(data_dev_dest, data_dev_src, bytes);
}

void acc_memcpy_device_async(d_void *data_dev_dest, d_void *data_dev_src, size_t bytes, int async_arg) {
    if (bytes == 0) {
        return;
    }

    if (data_dev_dest == data_dev_src) {
        return;
    }

    if (data_dev_dest == NULL || data_dev_src == NULL) {
        acc_error("acc_memcpy_device_async: Invalid null pointer");
        return;
    }

    if (bytes > acc_get_device_memory_size(data_dev_dest)) {
        acc_error("acc_memcpy_device_async: Invalid memory size");
        return;
    }

    if (bytes > acc_get_device_memory_size(data_dev_src)) {
        acc_error("acc_memcpy_device_async: Invalid memory size");
        return;
    }

    acc_async_memcpy(data_dev_dest, data_dev_src, bytes, async_arg);
}