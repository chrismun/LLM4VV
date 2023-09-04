#include <stdlib.h>
#include <stdio.h>
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

void acc_memcpy_to_device(d_void *data_dev_dest, h_void*data_host_src, size_t bytes){
    if (bytes == 0) {
        return;
    }

    if (data_dev_dest == NULL || data_host_src == NULL) {
        acc_error("acc_memcpy_to_device: data_dev_dest or data_host_src is NULL");
        return;
    }

    if (data_dev_dest == data_host_src) {
        return;
    }

    if (data_dev_dest < data_host_src || data_dev_dest > data_host_src + bytes) {
        acc_error("acc_memcpy_to_device: data_dev_dest is not accessible by the current device");
        return;
    }

    if (data_host_src < data_dev_dest || data_host_src > data_dev_dest + bytes) {
        acc_error("acc_memcpy_to_device: data_host_src is not accessible by the local thread");
        return;
    }

    memcpy(data_dev_dest, data_host_src, bytes);
}

void acc_memcpy_to_device_async(d_void *data_dev_dest, h_void*data_host_src, size_t bytes, int async_arg){
    if (bytes == 0) {
        return;
    }

    if (data_dev_dest == NULL || data_host_src == NULL) {
        acc_error("acc_memcpy_to_device_async: data_dev_dest or data_host_src is NULL");
        return;
    }

    if (data_dev_dest == data_host_src) {
        return;
    }

    if (data_dev_dest < data_host_src || data_dev_dest > data_host_src + bytes) {
        acc_error("acc_memcpy_to_device_async: data_dev_dest is not accessible by the current device");
        return;
    }

    if (data_host_src < data_dev_dest || data_host_src > data_dev_dest + bytes) {
        acc_error("acc_memcpy_to_device_async: data_host_src is not accessible by the local thread");
        return;
    }

    memcpy(data_dev_dest, data_host_src, bytes);
}