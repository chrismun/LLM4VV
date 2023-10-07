#include "acc_testsuite.h"

#ifndef T1
//T1:acc copyout,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some memory on the device
    int *device_data = (int *)acc_malloc(sizeof(int));

    // Copy some data to the device
    int host_data = 42;
    acc_copyin(device_data, &host_data, sizeof(int));

    // Copy the data back to the host
    int *host_data_copy = (int *)acc_malloc(sizeof(int));
    acc_copyout(host_data_copy, device_data, sizeof(int));

    // Check that the data was copied correctly
    if (*host_data_copy != host_data) {
        err = 1;
    }

    // Free the memory on the device
    acc_free(device_data);

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