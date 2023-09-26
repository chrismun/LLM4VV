#include "acc_testsuite.h"

#ifndef T1
//T1:acc memcpy device,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate memory on the device
    void *data_dev_src = acc_malloc(1024);
    void *data_dev_dest = acc_malloc(1024);

    // Initialize data on the device
    acc_memcpy_device(data_dev_src, "Hello, world!", 13);

    // Copy data from device to device
    acc_memcpy_device(data_dev_dest, data_dev_src, 13);

    // Check that the data was copied correctly
    char *data_host = (char *)acc_malloc_host(1024);
    acc_memcpy_host(data_host, data_dev_dest, 13);
    if (strcmp(data_host, "Hello, world!") != 0) {
        err = 1;
    }

    // Free memory on the device
    acc_free(data_dev_src);
    acc_free(data_dev_dest);
    acc_free_host(data_host);

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