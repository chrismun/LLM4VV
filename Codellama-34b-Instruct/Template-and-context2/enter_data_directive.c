#include "acc_testsuite.h"

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;

    // Create a data array
    int data[10];

    // Initialize the data array
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create an OpenACC region
    #pragma acc enter data copyin(data)

    // Check that the data has been copied into the device
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err++;
        }
    }

    // Exit the OpenACC region
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