#include "acc_testsuite.h"

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    #pragma acc data detach(data)
    {
        // Do some work with the data
    }

    // Check that the data has been detached
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

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