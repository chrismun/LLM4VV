#include "acc_testsuite.h"

#ifndef T1
//T1:acc copyin,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some memory on the host
    int *host_data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }

    // Copy the data to the device using acc_copyin
    int *device_data = (int *)acc_copyin(host_data, sizeof(int) * 10);

    // Check that the data has been copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != host_data[i]) {
            err++;
        }
    }

    // Free the memory on the host
    free(host_data);

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