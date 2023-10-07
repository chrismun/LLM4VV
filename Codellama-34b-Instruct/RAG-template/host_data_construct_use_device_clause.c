#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the data
    int *data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Use the host_data construct with the use_device clause to copy the data to the device
    #pragma acc host_data use_device(data)
    {
        // Copy the data to the device
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }
    }

    // Check that the data has been copied correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err++;
        }
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