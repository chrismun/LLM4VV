#include "acc_testsuite.h"
#ifndef T1
//T1:data,construct,copyout,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));

    // Ensuring initializing doesn't affect the test
    for (int i = 0; i < size; ++i){
        a[i] = -1;
    }
    
    // OpenACC region where we expect a[i] to be set to i, and then copied out.
#pragma acc data copyout(a[0:size])
    {
#pragma acc parallel loop
        for (int i = 0; i < size; ++i){
            a[i] = i;
        }
    }

    // Verify if copyout was successful
    for (int i = 0; i < size; ++i){
        if (a[i] != i){
            err += 1; // Increment error count if the data was not copied correctly.
        }
    }
    
    free(a);
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