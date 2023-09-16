#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    int a[N];
    int b[N];

    srand(SEED);

    // Initialize arrays
    for (int i = 0; i < N; ++i){
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Perform array addition using the OpenACC loop construct with worker clause
    #pragma acc parallel loop worker
    for (int i = 0; i < N; ++i){
        b[i] = a[i] + 1;
    }

    // Verify the correctness of the result
    for (int i = 0; i < N; ++i){
        if (b[i] != a[i] + 1){
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