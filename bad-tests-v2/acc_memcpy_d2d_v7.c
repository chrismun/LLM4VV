#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_num_dest = 0;
    int dev_num_src = 1;
    int async_arg_src = 0;
    int bytes = 1024;
    void *data_arg_dest = malloc(bytes);
    void *data_arg_src = malloc(bytes);

    // Initialize data on device 1
    for (int i = 0; i < bytes; i++) {
        ((char*)data_arg_src)[i] = i % 256;
    }

    // Copy data from device 1 to device 0
    acc_memcpy_d2d(data_arg_dest, data_arg_src, bytes, dev_num_dest, dev_num_src);

    // Verify that the data was copied correctly
    for (int i = 0; i < bytes; i++) {
        if (((char*)data_arg_dest)[i] != ((char*)data_arg_src)[i]) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(data_arg_dest);
    free(data_arg_src);

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