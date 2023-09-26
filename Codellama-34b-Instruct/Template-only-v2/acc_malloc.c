#include "acc_testsuite.h"
#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    void *dev_ptr = acc_malloc(sizeof(int));
    if (dev_ptr == NULL) {
        err = 1;
    }

    // Initialize the memory on the device
    int *dev_data = (int *)dev_ptr;
    *dev_data = 12345;

    // Copy the data from the device to the host
    int *host_data = (int *)acc_malloc(sizeof(int));
    acc_memcpy(host_data, dev_data, sizeof(int));

    // Check that the data was copied correctly
    if (*host_data != 12345) {
        err = 1;
    }

    // Free the memory on the device
    acc_free(dev_ptr);

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