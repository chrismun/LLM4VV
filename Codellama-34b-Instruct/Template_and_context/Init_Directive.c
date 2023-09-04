c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the runtime for the given device or devices of the given device type
    #pragma acc init device_type(gpu)

    // Allocate some data on the device
    int *data;
    #pragma acc enter data copyin(data[0:100])

    // Verify that the data has been initialized correctly
    for (int i = 0; i < 100; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    // Deallocate the data
    #pragma acc exit data delete(data)

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