#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare and initialize arrays
    int n = 100;
    int a[n];
    int b[n];
    int c[n];
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = n - i;
    }

    // Compute c[] asynchronously on the GPU using OpenACC
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    #pragma acc kernels async(1)
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
    
    // Wait for kernel to complete
    #pragma acc wait async(1)

    // Verify the correctness of the computation
    for (int i = 0; i < n; i++) {
        if (c[i] != (a[i] + b[i])) {
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