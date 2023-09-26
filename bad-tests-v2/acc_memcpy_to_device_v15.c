#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

int acc_memcpy_to_device(void *data_dev_dest, void *data_host_src, size_t bytes) {
    int err = 0;
    if (bytes == 0) {
        return err;
    }
    if (data_dev_dest == NULL || data_host_src == NULL) {
        err = acc_error_invalid_null_pointer;
        return err;
    }
    if (data_dev_dest == data_host_src) {
        return err;
    }
    if (bytes > acc_get_device_memory_size(data_dev_dest)) {
        err = acc_error_invalid_memory_size;
        return err;
    }
    if (acc_get_device_memory_type(data_dev_dest) != ACC_MEMORY_TYPE_DEVICE) {
        err = acc_error_invalid_memory_type;
        return err;
    }
    if (acc_get_device_memory_type(data_host_src) != ACC_MEMORY_TYPE_HOST) {
        err = acc_error_invalid_memory_type;
        return err;
    }
    if (acc_get_device_memory_overlap(data_dev_dest, data_host_src, bytes) != 0) {
        err = acc_error_invalid_memory_overlap;
        return err;
    }
    memcpy(data_dev_dest, data_host_src, bytes);
    return err;
}

int main() {
    int err = 0;
    void *data_dev_dest = acc_malloc(1024);
    void *data_host_src = malloc(1024);
    size_t bytes = 1024;
    err = acc_memcpy_to_device(data_dev_dest, data_host_src, bytes);
    if (err != 0) {
        printf("Error: %s\n", acc_error_string(err));
        return 1;
    }
    return 0;
}