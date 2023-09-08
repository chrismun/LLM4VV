#include "acc_testsuite.h"

#ifndef T1
//T1:data construct copyout clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b;

    // Initialize variables
    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    *a = 1;
    *b = 2;

    // Copy data from a to b
    #pragma acc data copyout(b[0:1])
    {
        #pragma acc parallel
        {
            b[0] = a[0];
        }
    }

    // Check that b[0] has been copied from a[0]
    if (b[0] != 1) {
        err = 1;
    }

    // Free memory
    free(a);
    free(b);

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