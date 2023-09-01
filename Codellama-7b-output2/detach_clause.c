#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[N];
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Create a detached data array
    int detached_data[N];
    for (int i = 0; i < N; i++) {
        detached_data[i] = i;
    }

    // Detach the data array
    #pragma acc detach(data)

    // Check that the detached data array is still accessible
    for (int i = 0; i < N; i++) {
        if (detached_data[i] != i) {
            err = 1;
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