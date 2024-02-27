#include "acc_testsuite.h"
#ifndef T1
//T1:loop,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size];
    int b[size];
    int c[size];

    // Initialize arrays
    for (int i = 0; i < size; ++i){
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = rand() / (RAND_MAX / 100);
    }

    // Compute on device
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop seq
        for (int i = 0; i < size; ++i){
            c[i] = a[i] + b[i];
        }
    }

    // Verify results
    for (int i = 0; i < size; ++i){
        if (c[i] != a[i] + b[i]){
            err++;
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