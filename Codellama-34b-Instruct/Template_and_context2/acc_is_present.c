#include "acc_testsuite.h"

#ifndef T1
//T1:acc is present,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some data on the host
    int *data = (int *)malloc(sizeof(int) * 10);

    // Initialize the data
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Check if the data is present on the device
    if (acc_is_present(data, sizeof(int) * 10) == 0) {
        // The data is not present on the device, so copy it
        acc_copyin(data, sizeof(int) * 10);
    }

    // Check if the data is present on the device again
    if (acc_is_present(data, sizeof(int) * 10) == 0) {
        // The data is still not present on the device, so there's an error
        err = 1;
    }

    // Free the data
    free(data);

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