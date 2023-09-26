#include "acc_testsuite.h"

#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create an OpenACC region
    #pragma acc enter data copyin(data)
    {
        // Do some work on the data
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            data[i] = data[i] * 2;
        }
    }

    // Exit the OpenACC region
    #pragma acc exit data delete(data)

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != i * 2) {
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