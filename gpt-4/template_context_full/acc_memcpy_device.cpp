#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
// acc_memcpy_device, Ver: 2.0 - 2.7 
int test1() {
    int err = 0;
    srand(SEED);
    size_t bytes = 1024;
    int *data_host_src = (int*)malloc(bytes);
    int *data_host_dest = (int*)malloc(bytes);
    for (int i = 0; i < bytes/sizeof(int); ++i)
        data_host_src[i] = rand();
    
    int *data_dev_src = (int*)acc_malloc(bytes);
    int *data_dev_dest = (int*)acc_malloc(bytes);

    acc_memcpy_to_device(data_dev_src, data_host_src, bytes);
    acc_memcpy_device(data_dev_dest, data_dev_src, bytes);
    acc_memcpy_from_device(data_host_dest, data_dev_dest, bytes);

    for (int i = 0; i < bytes/sizeof(int); ++i) {
        if (data_host_src[i] != data_host_dest[i]) {
            err = 1;
            break;
        }
    }
    acc_free(data_dev_src);
    acc_free(data_dev_dest);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}