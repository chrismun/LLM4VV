#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize arrays with random data
    int a[N], b[N], c[N];
    for (int i = 0; i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    // Use the tile clause to parallelize the computation
    #pragma acc parallel loop tile(N/2)
    for (int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    // Check that the result is correct
    for (int i = 0; i < N; i++){
        if (c[i] != (a[i] + b[i])){
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