#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize an array with random values
    int a[N];
    for (int i = 0; i < N; i++){
        a[i] = rand();
    }

    // Use the init directive to initialize another array with the same values
    int b[N];
    #pragma acc init(b[0:N])
    for (int i = 0; i < N; i++){
        b[i] = a[i];
    }

    // Check that the arrays are equal
    for (int i = 0; i < N; i++){
        if (a[i] != b[i]){
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