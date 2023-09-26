#include "acc_testsuite.h"

#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate memory on the device
    void *data_dev_src = acc_malloc(1024);
    void *data_host_dest = malloc(1024);

    // Initialize data on the device
    for (int i = 0; i < 1024; i++) {
        ((char*)data_dev_src)[i] = i;
    }

    // Copy data from the device to the host
    acc_memcpy_from_device(data_host_dest, data_dev_src, 1024);

    // Verify that the data was copied correctly
    for (int i = 0; i < 1024; i++) {
        if (((char*)data_host_dest)[i] != i) {
            err++;
        }
    }

    // Free memory on the device
    acc_free(data_dev_src);
    free(data_host_dest);

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