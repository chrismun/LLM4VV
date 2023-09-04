#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

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

void acc_memcpy_d2d(h_void *data_arg_dest, h_void *data_arg_src, size_t bytes, int dev_num_dest, int dev_num_src) {
    if (bytes == 0) {
        return;
    }

    if (data_arg_dest == data_arg_src && (dev_num_dest == dev_num_src || data_arg_dest == data_arg_src)) {
        return;
    }

    if (data_arg_dest == NULL || data_arg_src == NULL) {
        acc_error_invalid_null_pointer();
        return;
    }

    if (dev_num_dest < 0 || dev_num_src < 0) {
        acc_error_device_unavailable();
        return;
    }

    if (data_arg_dest != data_arg_src && !acc_is_present(data_arg_dest, dev_num_dest) && !acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_not_present();
        return;
    }

    if (data_arg_dest != data_arg_src && !acc_is_present(data_arg_dest, dev_num_dest) && acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_partly_present();
        return;
    }

    if (data_arg_dest != data_arg_src && acc_is_present(data_arg_dest, dev_num_dest) && !acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_partly_present();
        return;
    }

    if (data_arg_dest != data_arg_src && acc_is_present(data_arg_dest, dev_num_dest) && acc_is_present(data_arg_src, dev_num_src)) {
        memcpy(data_arg_dest, data_arg_src, bytes);
    }
}

void acc_memcpy_d2d_async(h_void *data_arg_dest, h_void *data_arg_src, size_t bytes, int dev_num_dest, int dev_num_src, int async_arg_src) {
    if (bytes == 0) {
        return;
    }

    if (data_arg_dest == data_arg_src && (dev_num_dest == dev_num_src || data_arg_dest == data_arg_src)) {
        return;
    }

    if (data_arg_dest == NULL || data_arg_src == NULL) {
        acc_error_invalid_null_pointer();
        return;
    }

    if (dev_num_dest < 0 || dev_num_src < 0) {
        acc_error_device_unavailable();
        return;
    }

    if (data_arg_dest != data_arg_src && !acc_is_present(data_arg_dest, dev_num_dest) && !acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_not_present();
        return;
    }

    if (data_arg_dest != data_arg_src && !acc_is_present(data_arg_dest, dev_num_dest) && acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_partly_present();
        return;
    }

    if (data_arg_dest != data_arg_src && acc_is_present(data_arg_dest, dev_num_dest) && !acc_is_present(data_arg_src, dev_num_src)) {
        acc_error_partly_present();
        return;
    }

    if (data_arg_dest != data_arg_src && acc_is_present(data_arg_dest, dev_num_dest) && acc_is_present(data_arg_src, dev_num_src)) {
        memcpy(data_arg_dest, data_arg_src, bytes);
    }
}