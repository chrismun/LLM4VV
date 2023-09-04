c
#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Test case 1: data is in shared memory or data_arg is a null pointer
    int *data = (int *)malloc(sizeof(int));
    *data = 1234;
    int *data_dev = (int *)acc_deviceptr(data);
    int *data_host = (int *)acc_hostptr(data_dev);
    if (data_host != data) {
        err = 1;
    }

    // Test case 2: data is not present in the current device memory
    int *data_not_present = (int *)malloc(sizeof(int));
    *data_not_present = 5678;
    int *data_not_present_dev = (int *)acc_deviceptr(data_not_present);
    int *data_not_present_host = (int *)acc_hostptr(data_not_present_dev);
    if (data_not_present_host != NULL) {
        err = 1;
    }

    // Test case 3: data corresponds to a host address that is present in the current device memory
    int *data_present = (int *)malloc(sizeof(int));
    *data_present = 9012;
    int *data_present_dev = (int *)acc_deviceptr(data_present);
    int *data_present_host = (int *)acc_hostptr(data_present_dev);
    if (data_present_host != data_present) {
        err = 1;
    }

    free(data);
    free(data_not_present);
    free(data_present);

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