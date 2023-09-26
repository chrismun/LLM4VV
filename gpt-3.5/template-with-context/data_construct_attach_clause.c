#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int*)malloc(sizeof(int) * N);

    // Attach data to the device
    #pragma acc enter data copyin(data[0:N]) attach(data)

    // Perform operations on the device
    #pragma acc parallel loop present(data)
    for(int i = 0; i < N; i++){
        data[i] = i;
    }

    // Detach data from the device
    #pragma acc exit data delete(data[0:N]) detach(data)

    // Verify the results
    for(int i = 0; i < N; i++){
        if(data[i] != i){
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