#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(sizeof(int) * 10);
    int *attach_data = (int *)malloc(sizeof(int) * 10);

    // Initialize data
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Attach data to the device
    #pragma acc attach(data, attach_data)

    // Perform some operations on the data
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        data[i] += attach_data[i];
    }

    // Detach data from the device
    #pragma acc detach(data, attach_data)

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != i + attach_data[i]) {
            err = 1;
            break;
        }
    }

    free(data);
    free(attach_data);

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