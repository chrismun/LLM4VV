#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a device array
    int device_data[10];
    #pragma acc enter data copyin(data[:10])
    #pragma acc parallel loop async(1)
    for (int i = 0; i < 10; i++) {
        device_data[i] = data[i];
    }
    #pragma acc exit data delete(device_data[:10])

    // Verify that the data has been copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

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