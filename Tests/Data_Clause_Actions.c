#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the data array
    int data[N];
    for (int i = 0; i < N; i++){
        data[i] = i;
    }

    // Create a kernel that modifies the data array
    #pragma acc parallel loop
    for (int i = 0; i < N; i++){
        data[i] = data[i] * 2;
    }

    // Verify that the data array has been modified correctly
    for (int i = 0; i < N; i++){
        if (data[i] != i * 2){
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