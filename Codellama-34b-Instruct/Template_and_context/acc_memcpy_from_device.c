#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_runtime.h>

int acc_memcpy_from_device(void *data_host_dest, void *data_dev_src, size_t bytes) {
    int err = 0;

    if (bytes == 0) {
        return 0;
    }

    if (data_host_dest == NULL || data_dev_src == NULL) {
        err = acc_error_invalid_null_pointer;
        goto error;
    }

    if (acc_deviceptr_is_shared(data_dev_src) && acc_hostptr_is_shared(data_host_dest)) {
        if (acc_deviceptr_is_same(data_dev_src, data_host_dest)) {
            return 0;
        }
        if (acc_deviceptr_overlap(data_dev_src, data_host_dest, bytes)) {
            err = acc_error_invalid_async;
            goto error;
        }
    }

    if (!acc_deviceptr_is_accessible(data_dev_src)) {
        err = acc_error_invalid_async;
        goto error;
    }

    if (!acc_hostptr_is_accessible(data_host_dest)) {
        err = acc_error_invalid_async;
        goto error;
    }

    memcpy(data_host_dest, data_dev_src, bytes);

    return 0;

error:
    acc_error_handler(err);
    return 1;
}