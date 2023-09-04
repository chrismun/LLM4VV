#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Copy the data array to the device
    acc_copyin(data, 100);

    // Create a copy of the data array on the device
    int *device_data = acc_copyout(data, 100);

    // Modify the data array on the device
    for (int i = 0; i < 100; i++) {
        device_data[i] = i * 2;
    }

    // Copy the modified data array back to the host
    acc_copyin(device_data, 100);

    // Check that the data array on the host has been modified
    for (int i = 0; i < 100; i++) {
        if (data[i] != i * 2) {
            err = 1;
            break;
        }
    }

    // Delete the data array on the device
    acc_delete(device_data);

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