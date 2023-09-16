#include "acc_testsuite.h"
#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for(i=0; i<N; i++){
        a[i] = i;
        b[i] = i;
    }

    // Compute c[i] = a[i] + b[i]
    #pragma acc data detach(a, b)
    {
        #pragma acc kernels
        for(i=0; i<N; i++){
            c[i] = a[i] + b[i];
        }
    }

    // Verify result
    for(i=0; i<N; i++){
        if(c[i] != 2*i){
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