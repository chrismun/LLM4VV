#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the data arrays
    int a[N];
    int b[N];
    for (int i = 0; i < N; i++){
        a[i] = rand();
        b[i] = rand();
    }

    // Declare the data clauses
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])

    // Execute the kernel
    #pragma acc kernels loop independent
    for (int i = 0; i < N; i++){
        b[i] = a[i] * 2;
    }

    // Verify the results
    for (int i = 0; i < N; i++){
        if (b[i] != a[i] * 2){
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