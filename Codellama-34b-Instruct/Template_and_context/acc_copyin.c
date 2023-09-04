#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random data section
    int data_size = rand() % 1000 + 1;
    char* data = (char*)malloc(data_size);
    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 256;
    }

    // Copy the data to the device memory
    char* device_data = (char*)acc_copyin(data, data_size);
    if (device_data == NULL) {
        err = 1;
    }

    // Verify that the data has been copied correctly
    for (int i = 0; i < data_size; i++) {
        if (device_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
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