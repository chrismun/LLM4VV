#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    // Initialize the arrays
    for (int i = 0; i < n; ++i){
        a[i] = rand() % n;
        b[i] = 0;
    }

    // Perform computation on GPU
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            b[i] = a[i] + 1;
        }
    }

    // Verify the results
    for (int i = 0; i < n; ++i){
        if (b[i] != a[i] + 1){
            err = 1;
            break;
        }
    }

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
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}